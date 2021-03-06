#include "linux/autoconf.h"
/*
 * IPv6 packet mangling table, a port of the IPv4 mangle table to IPv6
 *
 * Copyright (C) 2000 by Harald Welte <laforge@gnumonks.org>
 */
#include <linux/module.h>
#include <linux/netfilter_ipv6/ip6_tables.h>

#define MANGLE_VALID_HOOKS ((1 << NF_IP6_PRE_ROUTING) | (1 << NF_IP6_LOCAL_OUT))

#if 1
#define DEBUGP(x, args...)	printk(KERN_DEBUG x, ## args)
#else
#define DEBUGP(x, args...)
#endif

/* Standard entry. */
struct ip6t_standard
{
	struct ip6t_entry entry;
	struct ip6t_standard_target target;
};

struct ip6t_error_target
{
	struct ip6t_entry_target target;
	char errorname[IP6T_FUNCTION_MAXNAMELEN];
};

struct ip6t_error
{
	struct ip6t_entry entry;
	struct ip6t_error_target target;
};

static struct
{
	struct ip6t_replace repl;
	struct ip6t_standard entries[2];
	struct ip6t_error term;
} initial_table __initdata
= { { "mangle", MANGLE_VALID_HOOKS, 3,
      sizeof(struct ip6t_standard) * 2 + sizeof(struct ip6t_error),
      { [NF_IP6_PRE_ROUTING] 0,
	[NF_IP6_LOCAL_OUT] sizeof(struct ip6t_standard) },
      { [NF_IP6_PRE_ROUTING] 0,
	[NF_IP6_LOCAL_OUT] sizeof(struct ip6t_standard) },
      0, NULL, { } },
    {
	    /* PRE_ROUTING */
	    { { { { { { 0 } } }, { { { 0 } } }, { { { 0 } } }, { { { 0 } } }, "", "", { 0 }, { 0 }, 0, 0, 0 },
		0,
		sizeof(struct ip6t_entry),
		sizeof(struct ip6t_standard),
		0, { 0, 0 }, { } },
	      { { { { IP6T_ALIGN(sizeof(struct ip6t_standard_target)), "" } }, { } },
		-NF_ACCEPT - 1 } },
	    /* LOCAL_OUT */
	    { { { { { { 0 } } }, { { { 0 } } }, { { { 0 } } }, { { { 0 } } }, "", "", { 0 }, { 0 }, 0, 0, 0 },
		0,
		sizeof(struct ip6t_entry),
		sizeof(struct ip6t_standard),
		0, { 0, 0 }, { } },
	      { { { { IP6T_ALIGN(sizeof(struct ip6t_standard_target)), "" } }, { } },
		-NF_ACCEPT - 1 } }
    },
    /* ERROR */
    { { { { { { 0 } } }, { { { 0 } } }, { { { 0 } } }, { { { 0 } } }, "", "", { 0 }, { 0 }, 0, 0, 0 },
	0,
	sizeof(struct ip6t_entry),
	sizeof(struct ip6t_error),
	0, { 0, 0 }, { } },
      { { { { IP6T_ALIGN(sizeof(struct ip6t_error_target)), IP6T_ERROR_TARGET } },
	  { } },
	"ERROR"
      }
    }
};

static struct ip6t_table packet_mangler
= { { NULL, NULL }, "mangle", &initial_table.repl,
    MANGLE_VALID_HOOKS, RW_LOCK_UNLOCKED, NULL };

/* The work comes in here from netfilter.c. */
static unsigned int
ip6t_hook(unsigned int hook,
	 struct sk_buff **pskb,
	 const struct net_device *in,
	 const struct net_device *out,
	 int (*okfn)(struct sk_buff *))
{
	return ip6t_do_table(pskb, hook, in, out, &packet_mangler, NULL);
}

static unsigned int
ip6t_local_out_hook(unsigned int hook,
		   struct sk_buff **pskb,
		   const struct net_device *in,
		   const struct net_device *out,
		   int (*okfn)(struct sk_buff *))
{

	unsigned long nfmark;
	unsigned int ret;
	struct in6_addr saddr, daddr;
	u_int8_t hop_limit;
	u_int32_t flowlabel;

#if 0
	/* root is playing with raw sockets. */
	if ((*pskb)->len < sizeof(struct iphdr)
	    || (*pskb)->nh.iph->ihl * 4 < sizeof(struct iphdr)) {
		if (net_ratelimit())
			printk("ip6t_hook: happy cracking.\n");
		return NF_ACCEPT;
	}
#endif

	/* save source/dest address, nfmark, hoplimit, flowlabel, priority,  */
	memcpy(&saddr, &(*pskb)->nh.ipv6h->saddr, sizeof(saddr));
	memcpy(&daddr, &(*pskb)->nh.ipv6h->daddr, sizeof(daddr));
	nfmark = (*pskb)->nfmark;
	hop_limit = (*pskb)->nh.ipv6h->hop_limit;

	/* flowlabel and prio (includes version, which shouldn't change either */
	flowlabel = (u_int32_t) (*pskb)->nh.ipv6h;

	ret = ip6t_do_table(pskb, hook, in, out, &packet_mangler, NULL);

	if (ret != NF_DROP && ret != NF_STOLEN 
		&& (memcmp(&(*pskb)->nh.ipv6h->saddr, &saddr, sizeof(saddr))
		    || memcmp(&(*pskb)->nh.ipv6h->daddr, &daddr, sizeof(daddr))
		    || (*pskb)->nfmark != nfmark
		    || (*pskb)->nh.ipv6h->hop_limit != hop_limit)) {

		/* something which could affect routing has changed */

		DEBUGP("ip6table_mangle: we'd need to re-route a packet\n");
	}

	return ret;
}

static struct nf_hook_ops ip6t_ops[]
= { { { NULL, NULL }, ip6t_hook, PF_INET6, NF_IP6_PRE_ROUTING, NF_IP6_PRI_MANGLE },
    { { NULL, NULL }, ip6t_local_out_hook, PF_INET6, NF_IP6_LOCAL_OUT,
		NF_IP6_PRI_MANGLE }
};

static int __init init(void)
{
	int ret;

	/* Register table */
	ret = ip6t_register_table(&packet_mangler);
	if (ret < 0)
		return ret;

	/* Register hooks */
	ret = nf_register_hook(&ip6t_ops[0]);
	if (ret < 0)
		goto cleanup_table;

	ret = nf_register_hook(&ip6t_ops[1]);
	if (ret < 0)
		goto cleanup_hook0;

	return ret;

 cleanup_hook0:
	nf_unregister_hook(&ip6t_ops[0]);
 cleanup_table:
	ip6t_unregister_table(&packet_mangler);

	return ret;
}

static void __exit fini(void)
{
	unsigned int i;

	for (i = 0; i < sizeof(ip6t_ops)/sizeof(struct nf_hook_ops); i++)
		nf_unregister_hook(&ip6t_ops[i]);

	ip6t_unregister_table(&packet_mangler);
}

module_init(init);
module_exit(fini);
