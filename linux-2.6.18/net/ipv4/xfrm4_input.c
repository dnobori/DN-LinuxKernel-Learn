#include "linux/autoconf.h"
/*
 * xfrm4_input.c
 *
 * Changes:
 *	YOSHIFUJI Hideaki @USAGI
 *		Split up af-specific portion
 *	Derek Atkins <derek@ihtfp.com>
 *		Add Encapsulation support
 * 	
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <net/ip.h>
#include <net/xfrm.h>

int xfrm4_rcv(struct sk_buff *skb)
{
	return xfrm4_rcv_encap(skb, 0);
}

EXPORT_SYMBOL(xfrm4_rcv);

static int xfrm4_parse_spi(struct sk_buff *skb, u8 nexthdr, u32 *spi, u32 *seq)
{
	switch (nexthdr) {
	case IPPROTO_IPIP:
		*spi = skb->nh.iph->saddr;
		*seq = 0;
		return 0;
	}

	return xfrm_parse_spi(skb, nexthdr, spi, seq);
}

#ifdef CONFIG_NETFILTER
static inline int xfrm4_rcv_encap_finish(struct sk_buff *skb)
{
	struct iphdr *iph = skb->nh.iph;

	if (skb->dst == NULL) {
		if (ip_route_input(skb, iph->daddr, iph->saddr, iph->tos,
		                   skb->dev))
			goto drop;
	}
	return dst_input(skb);
drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}
#endif

int xfrm4_rcv_encap(struct sk_buff *skb, __u16 encap_type)
{
	int err;
	u32 spi, seq;
	struct xfrm_state *xfrm_vec[XFRM_MAX_DEPTH];
	struct xfrm_state *x;
	int xfrm_nr = 0;
	int decaps = 0;

	if ((err = xfrm4_parse_spi(skb, skb->nh.iph->protocol, &spi, &seq)) != 0)
		goto drop;

	do {
		struct iphdr *iph = skb->nh.iph;

		if (xfrm_nr == XFRM_MAX_DEPTH)
			goto drop;

		x = xfrm_state_lookup((xfrm_address_t *)&iph->daddr, spi, iph->protocol, AF_INET);
		if (x == NULL)
			goto drop;

		spin_lock(&x->lock);
		if (unlikely(x->km.state != XFRM_STATE_VALID))
			goto drop_unlock;

		if ((x->encap ? x->encap->encap_type : 0) != encap_type)
			goto drop_unlock;

		if (x->props.replay_window && xfrm_replay_check(x, seq))
			goto drop_unlock;

		if (xfrm_state_check_expire(x))
			goto drop_unlock;

		if (x->type->input(x, skb))
			goto drop_unlock;

		/* only the first xfrm gets the encap type */
		encap_type = 0;

		if (x->props.replay_window)
			xfrm_replay_advance(x, seq);

		x->curlft.bytes += skb->len;
		x->curlft.packets++;

		spin_unlock(&x->lock);

		xfrm_vec[xfrm_nr++] = x;

		if (x->mode->input(x, skb))
			goto drop;

		if (x->props.mode) {
			decaps = 1;
			break;
		}

		if ((err = xfrm_parse_spi(skb, skb->nh.iph->protocol, &spi, &seq)) < 0)
			goto drop;
	} while (!err);

	/* Allocate new secpath or COW existing one. */

	if (!skb->sp || atomic_read(&skb->sp->refcnt) != 1) {
		struct sec_path *sp;
		sp = secpath_dup(skb->sp);
		if (!sp)
			goto drop;
		if (skb->sp)
			secpath_put(skb->sp);
		skb->sp = sp;
	}
	if (xfrm_nr + skb->sp->len > XFRM_MAX_DEPTH)
		goto drop;

	memcpy(skb->sp->xvec + skb->sp->len, xfrm_vec,
	       xfrm_nr * sizeof(xfrm_vec[0]));
	skb->sp->len += xfrm_nr;

	nf_reset(skb);

	if (decaps) {
		if (!(skb->dev->flags&IFF_LOOPBACK)) {
			dst_release(skb->dst);
			skb->dst = NULL;
		}
		netif_rx(skb);
		return 0;
	} else {
#ifdef CONFIG_NETFILTER
		__skb_push(skb, skb->data - skb->nh.raw);
		skb->nh.iph->tot_len = htons(skb->len);
		ip_send_check(skb->nh.iph);

		NF_HOOK(PF_INET, NF_IP_PRE_ROUTING, skb, skb->dev, NULL,
		        xfrm4_rcv_encap_finish);
		return 0;
#else
		return -skb->nh.iph->protocol;
#endif
	}

drop_unlock:
	spin_unlock(&x->lock);
	xfrm_state_put(x);
drop:
	while (--xfrm_nr >= 0)
		xfrm_state_put(xfrm_vec[xfrm_nr]);

	kfree_skb(skb);
	return 0;
}
