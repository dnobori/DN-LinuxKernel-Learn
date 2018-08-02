#include "linux/autoconf.h"
/*
 * Generic HDLC support routines for Linux
 *
 * Copyright (C) 1999 - 2005 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * Currently supported:
 *	* raw IP-in-HDLC
 *	* Cisco HDLC
 *	* Frame Relay with ANSI or CCITT LMI (both user and network side)
 *	* PPP
 *	* X.25
 *
 * Use sethdlc utility to set line parameters, protocol and PVCs
 *
 * How does it work:
 * - proto.open(), close(), start(), stop() calls are serialized.
 *   The order is: open, [ start, stop ... ] close ...
 * - proto.start() and stop() are called with spin_lock_irq held.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/errno.h>
#include <linux/if_arp.h>
#include <linux/init.h>
#include <linux/skbuff.h>
#include <linux/pkt_sched.h>
#include <linux/inetdevice.h>
#include <linux/lapb.h>
#include <linux/rtnetlink.h>
#include <linux/notifier.h>
#include <linux/hdlc.h>


static const char* version = "HDLC support module revision 1.19";

#undef DEBUG_LINK


static int hdlc_change_mtu(struct net_device *dev, int new_mtu)
{
	if ((new_mtu < 68) || (new_mtu > HDLC_MAX_MTU))
		return -EINVAL;
	dev->mtu = new_mtu;
	return 0;
}



static struct net_device_stats *hdlc_get_stats(struct net_device *dev)
{
	return hdlc_stats(dev);
}



static int hdlc_rcv(struct sk_buff *skb, struct net_device *dev,
		    struct packet_type *p, struct net_device *orig_dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	if (hdlc->proto.netif_rx)
		return hdlc->proto.netif_rx(skb);

	hdlc->stats.rx_dropped++; /* Shouldn't happen */
	dev_kfree_skb(skb);
	return NET_RX_DROP;
}



static inline void hdlc_proto_start(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	if (hdlc->proto.start)
		return hdlc->proto.start(dev);
}



static inline void hdlc_proto_stop(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	if (hdlc->proto.stop)
		return hdlc->proto.stop(dev);
}



static int hdlc_device_event(struct notifier_block *this, unsigned long event,
			     void *ptr)
{
	struct net_device *dev = ptr;
	hdlc_device *hdlc;
	unsigned long flags;
	int on;
 
	if (dev->get_stats != hdlc_get_stats)
		return NOTIFY_DONE; /* not an HDLC device */
 
	if (event != NETDEV_CHANGE)
		return NOTIFY_DONE; /* Only interrested in carrier changes */

	on = netif_carrier_ok(dev);

#ifdef DEBUG_LINK
	printk(KERN_DEBUG "%s: hdlc_device_event NETDEV_CHANGE, carrier %i\n",
	       dev->name, on);
#endif

	hdlc = dev_to_hdlc(dev);
	spin_lock_irqsave(&hdlc->state_lock, flags);

	if (hdlc->carrier == on)
		goto carrier_exit; /* no change in DCD line level */

	hdlc->carrier = on;

	if (!hdlc->open)
		goto carrier_exit;

	if (hdlc->carrier) {
		printk(KERN_INFO "%s: Carrier detected\n", dev->name);
		hdlc_proto_start(dev);
	} else {
		printk(KERN_INFO "%s: Carrier lost\n", dev->name);
		hdlc_proto_stop(dev);
	}

carrier_exit:
	spin_unlock_irqrestore(&hdlc->state_lock, flags);
	return NOTIFY_DONE;
}



/* Must be called by hardware driver when HDLC device is being opened */
int hdlc_open(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
#ifdef DEBUG_LINK
	printk(KERN_DEBUG "hdlc_open() carrier %i open %i\n",
	       hdlc->carrier, hdlc->open);
#endif

	if (hdlc->proto.id == -1)
		return -ENOSYS;	/* no protocol attached */

	if (hdlc->proto.open) {
		int result = hdlc->proto.open(dev);
		if (result)
			return result;
	}

	spin_lock_irq(&hdlc->state_lock);

	if (hdlc->carrier) {
		printk(KERN_INFO "%s: Carrier detected\n", dev->name);
		hdlc_proto_start(dev);
	} else
		printk(KERN_INFO "%s: No carrier\n", dev->name);

	hdlc->open = 1;

	spin_unlock_irq(&hdlc->state_lock);
	return 0;
}



/* Must be called by hardware driver when HDLC device is being closed */
void hdlc_close(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
#ifdef DEBUG_LINK
	printk(KERN_DEBUG "hdlc_close() carrier %i open %i\n",
	       hdlc->carrier, hdlc->open);
#endif

	spin_lock_irq(&hdlc->state_lock);

	hdlc->open = 0;
	if (hdlc->carrier)
		hdlc_proto_stop(dev);

	spin_unlock_irq(&hdlc->state_lock);

	if (hdlc->proto.close)
		hdlc->proto.close(dev);
}



#ifndef CONFIG_HDLC_RAW
#define hdlc_raw_ioctl(dev, ifr)	-ENOSYS
#endif

#ifndef CONFIG_HDLC_RAW_ETH
#define hdlc_raw_eth_ioctl(dev, ifr)	-ENOSYS
#endif

#ifndef CONFIG_HDLC_PPP
#define hdlc_ppp_ioctl(dev, ifr)	-ENOSYS
#endif

#ifndef CONFIG_HDLC_CISCO
#define hdlc_cisco_ioctl(dev, ifr)	-ENOSYS
#endif

#ifndef CONFIG_HDLC_FR
#define hdlc_fr_ioctl(dev, ifr)		-ENOSYS
#endif

#ifndef CONFIG_HDLC_X25
#define hdlc_x25_ioctl(dev, ifr)	-ENOSYS
#endif


int hdlc_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	unsigned int proto;

	if (cmd != SIOCWANDEV)
		return -EINVAL;

	switch(ifr->ifr_settings.type) {
	case IF_PROTO_HDLC:
	case IF_PROTO_HDLC_ETH:
	case IF_PROTO_PPP:
	case IF_PROTO_CISCO:
	case IF_PROTO_FR:
	case IF_PROTO_X25:
		proto = ifr->ifr_settings.type;
		break;

	default:
		proto = hdlc->proto.id;
	}

	switch(proto) {
	case IF_PROTO_HDLC:	return hdlc_raw_ioctl(dev, ifr);
	case IF_PROTO_HDLC_ETH:	return hdlc_raw_eth_ioctl(dev, ifr);
	case IF_PROTO_PPP:	return hdlc_ppp_ioctl(dev, ifr);
	case IF_PROTO_CISCO:	return hdlc_cisco_ioctl(dev, ifr);
	case IF_PROTO_FR:	return hdlc_fr_ioctl(dev, ifr);
	case IF_PROTO_X25:	return hdlc_x25_ioctl(dev, ifr);
	default:		return -EINVAL;
	}
}

void hdlc_setup(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);

	dev->get_stats = hdlc_get_stats;
	dev->change_mtu = hdlc_change_mtu;
	dev->mtu = HDLC_MAX_MTU;

	dev->type = ARPHRD_RAWHDLC;
	dev->hard_header_len = 16;

	dev->flags = IFF_POINTOPOINT | IFF_NOARP;

	hdlc->proto.id = -1;
	hdlc->proto.detach = NULL;
	hdlc->carrier = 1;
	hdlc->open = 0;
	spin_lock_init(&hdlc->state_lock);
}

struct net_device *alloc_hdlcdev(void *priv)
{
	struct net_device *dev;
	dev = alloc_netdev(sizeof(hdlc_device), "hdlc%d", hdlc_setup);
	if (dev)
		dev_to_hdlc(dev)->priv = priv;
	return dev;
}

void unregister_hdlc_device(struct net_device *dev)
{
	rtnl_lock();
	hdlc_proto_detach(dev_to_hdlc(dev));
	unregister_netdevice(dev);
	rtnl_unlock();
}



MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("HDLC support module");
MODULE_LICENSE("GPL v2");

EXPORT_SYMBOL(hdlc_open);
EXPORT_SYMBOL(hdlc_close);
EXPORT_SYMBOL(hdlc_ioctl);
EXPORT_SYMBOL(hdlc_setup);
EXPORT_SYMBOL(alloc_hdlcdev);
EXPORT_SYMBOL(unregister_hdlc_device);

static struct packet_type hdlc_packet_type = {
	.type = __constant_htons(ETH_P_HDLC),
	.func = hdlc_rcv,
};


static struct notifier_block hdlc_notifier = {
        .notifier_call = hdlc_device_event,
};


static int __init hdlc_module_init(void)
{
	int result;

	printk(KERN_INFO "%s\n", version);
	if ((result = register_netdevice_notifier(&hdlc_notifier)) != 0)
                return result;
        dev_add_pack(&hdlc_packet_type);
	return 0;
}



static void __exit hdlc_module_exit(void)
{
	dev_remove_pack(&hdlc_packet_type);
	unregister_netdevice_notifier(&hdlc_notifier);
}


module_init(hdlc_module_init);
module_exit(hdlc_module_exit);
