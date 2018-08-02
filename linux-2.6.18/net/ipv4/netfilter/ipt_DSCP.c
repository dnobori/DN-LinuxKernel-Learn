#include "linux/autoconf.h"
/* iptables module for setting the IPv4 DSCP field, Version 1.8
 *
 * (C) 2002 by Harald Welte <laforge@netfilter.org>
 * based on ipt_FTOS.c (C) 2000 by Matthew G. Marsh <mgm@paktronix.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation.
 * 
 * See RFC2474 for a description of the DSCP field within the IP Header.
 *
 * ipt_DSCP.c,v 1.8 2002/08/06 18:41:57 laforge Exp
*/

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/checksum.h>

#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_DSCP.h>

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("iptables DSCP modification module");
MODULE_LICENSE("GPL");

static unsigned int
target(struct sk_buff **pskb,
       const struct net_device *in,
       const struct net_device *out,
       unsigned int hooknum,
       const struct xt_target *target,
       const void *targinfo,
       void *userinfo)
{
	const struct ipt_DSCP_info *dinfo = targinfo;
	u_int8_t sh_dscp = ((dinfo->dscp << IPT_DSCP_SHIFT) & IPT_DSCP_MASK);


	if (((*pskb)->nh.iph->tos & IPT_DSCP_MASK) != sh_dscp) {
		u_int16_t diffs[2];

		if (!skb_make_writable(pskb, sizeof(struct iphdr)))
			return NF_DROP;

		diffs[0] = htons((*pskb)->nh.iph->tos) ^ 0xFFFF;
		(*pskb)->nh.iph->tos = ((*pskb)->nh.iph->tos & ~IPT_DSCP_MASK)
			| sh_dscp;
		diffs[1] = htons((*pskb)->nh.iph->tos);
		(*pskb)->nh.iph->check
			= csum_fold(csum_partial((char *)diffs,
						 sizeof(diffs),
						 (*pskb)->nh.iph->check
						 ^ 0xFFFF));
	}
	return IPT_CONTINUE;
}

static int
checkentry(const char *tablename,
	   const void *e_void,
	   const struct xt_target *target,
           void *targinfo,
           unsigned int targinfosize,
           unsigned int hook_mask)
{
	const u_int8_t dscp = ((struct ipt_DSCP_info *)targinfo)->dscp;

	if ((dscp > IPT_DSCP_MAX)) {
		printk(KERN_WARNING "DSCP: dscp %x out of range\n", dscp);
		return 0;
	}
	return 1;
}

static struct ipt_target ipt_dscp_reg = {
	.name		= "DSCP",
	.target		= target,
	.targetsize	= sizeof(struct ipt_DSCP_info),
	.table		= "mangle",
	.checkentry	= checkentry,
	.me		= THIS_MODULE,
};

static int __init ipt_dscp_init(void)
{
	return ipt_register_target(&ipt_dscp_reg);
}

static void __exit ipt_dscp_fini(void)
{
	ipt_unregister_target(&ipt_dscp_reg);
}

module_init(ipt_dscp_init);
module_exit(ipt_dscp_fini);
