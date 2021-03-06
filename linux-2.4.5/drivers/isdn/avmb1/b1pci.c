#include "linux/autoconf.h"
/*
 * $Id: b1pci.c,v 1.29.6.3 2001/04/20 02:41:59 keil Exp $
 * 
 * Module for AVM B1 PCI-card.
 * 
 * (c) Copyright 1999 by Carsten Paeth (calle@calle.in-berlin.de)
 * 
 * $Log: b1pci.c,v $
 * Revision 1.29.6.3  2001/04/20 02:41:59  keil
 * changes from mainstream
 *
 * Revision 1.29.6.2  2001/03/21 08:52:21  kai
 * merge from main branch: fix buffer for revision string (calle)
 *
 * Revision 1.29.6.1  2000/11/28 12:02:45  kai
 * MODULE_DEVICE_TABLE for 2.4
 *
 * Revision 1.29.2.2  2000/11/26 17:47:53  kai
 * added PCI_DEV_TABLE for 2.4
 *
 * Revision 1.29.2.1  2000/11/26 17:14:19  kai
 * fix device ids
 * also needs patches to include/linux/pci_ids.h
 *
 * Revision 1.29  2000/11/23 20:45:14  kai
 * fixed module_init/exit stuff
 * Note: compiled-in kernel doesn't work pre 2.2.18 anymore.
 *
 * Revision 1.28  2000/11/01 14:05:02  calle
 * - use module_init/module_exit from linux/init.h.
 * - all static struct variables are initialized with "membername:" now.
 * - avm_cs.c, let it work with newer pcmcia-cs.
 *
 * Revision 1.27  2000/08/08 09:24:19  calle
 * calls to pci_enable_device surounded by #ifndef COMPAT_HAS_2_2_PCI
 *
 * Revision 1.26  2000/07/20 10:21:21  calle
 * Bugfix: driver will not be unregistered, if not cards were detected.
 *         this result in an oops in kcapi.c
 *
 * Revision 1.25  2000/05/29 12:29:18  keil
 * make pci_enable_dev compatible to 2.2 kernel versions
 *
 * Revision 1.24  2000/05/19 15:43:22  calle
 * added calls to pci_device_start().
 *
 * Revision 1.23  2000/05/06 00:52:36  kai
 * merged changes from kernel tree
 * fixed timer and net_device->name breakage
 *
 * Revision 1.22  2000/04/21 13:01:33  calle
 * Revision in b1pciv4 driver was missing.
 *
 * Revision 1.21  2000/04/03 13:29:24  calle
 * make Tim Waugh happy (module unload races in 2.3.99-pre3).
 * no real problem there, but now it is much cleaner ...
 *
 * Revision 1.20  2000/02/02 18:36:03  calle
 * - Modules are now locked while init_module is running
 * - fixed problem with memory mapping if address is not aligned
 *
 * Revision 1.19  2000/01/25 14:33:38  calle
 * - Added Support AVM B1 PCI V4.0 (tested with prototype)
 *   - splitted up t1pci.c into b1dma.c for common function with b1pciv4
 *   - support for revision register
 *
 * Revision 1.18  1999/11/05 16:38:01  calle
 * Cleanups before kernel 2.4:
 * - Changed all messages to use card->name or driver->name instead of
 *   constant string.
 * - Moved some data from struct avmcard into new struct avmctrl_info.
 *   Changed all lowlevel capi driver to match the new structur.
 *
 * Revision 1.17  1999/10/05 06:50:07  calle
 * Forgot SA_SHIRQ as argument to request_irq.
 *
 * Revision 1.16  1999/08/11 21:01:07  keil
 * new PCI codefix
 *
 * Revision 1.15  1999/08/10 16:02:27  calle
 * struct pci_dev changed in 2.3.13. Made the necessary changes.
 *
 * Revision 1.14  1999/07/09 15:05:41  keil
 * compat.h is now isdn_compat.h
 *
 * Revision 1.13  1999/07/05 15:09:50  calle
 * - renamed "appl_release" to "appl_released".
 * - version und profile data now cleared on controller reset
 * - extended /proc interface, to allow driver and controller specific
 *   informations to include by driver hackers.
 *
 * Revision 1.12  1999/07/01 15:26:29  calle
 * complete new version (I love it):
 * + new hardware independed "capi_driver" interface that will make it easy to:
 *   - support other controllers with CAPI-2.0 (i.e. USB Controller)
 *   - write a CAPI-2.0 for the passive cards
 *   - support serial link CAPI-2.0 boxes.
 * + wrote "capi_driver" for all supported cards.
 * + "capi_driver" (supported cards) now have to be configured with
 *   make menuconfig, in the past all supported cards where included
 *   at once.
 * + new and better informations in /proc/capi/
 * + new ioctl to switch trace of capi messages per controller
 *   using "avmcapictrl trace [contr] on|off|...."
 * + complete testcircle with all supported cards and also the
 *   PCMCIA cards (now patch for pcmcia-cs-3.0.13 needed) done.
 *
 *
 */

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/capi.h>
#include <asm/io.h>
#include <linux/init.h>
#include "capicmd.h"
#include "capiutil.h"
#include "capilli.h"
#include "avmcard.h"

static char *revision = "$Revision: 1.29.6.4 $";

/* ------------------------------------------------------------- */

static struct pci_device_id b1pci_pci_tbl[] __initdata = {
	{ PCI_VENDOR_ID_AVM, PCI_DEVICE_ID_AVM_B1, PCI_ANY_ID, PCI_ANY_ID },
	{ }				/* Terminating entry */
};

MODULE_DEVICE_TABLE(pci, b1pci_pci_tbl);
MODULE_AUTHOR("Carsten Paeth <calle@calle.in-berlin.de>");

/* ------------------------------------------------------------- */

static struct capi_driver_interface *di;

/* ------------------------------------------------------------- */

static void b1pci_interrupt(int interrupt, void *devptr, struct pt_regs *regs)
{
	avmcard *card;

	card = (avmcard *) devptr;

	if (!card) {
		printk(KERN_WARNING "b1pci: interrupt: wrong device\n");
		return;
	}
	if (card->interrupt) {
		printk(KERN_ERR "%s: reentering interrupt hander.\n", card->name);
		return;
	}

	card->interrupt = 1;

	b1_handle_interrupt(card);

	card->interrupt = 0;
}
/* ------------------------------------------------------------- */

static void b1pci_remove_ctr(struct capi_ctr *ctrl)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	unsigned int port = card->port;

	b1_reset(port);
	b1_reset(port);

	di->detach_ctr(ctrl);
	free_irq(card->irq, card);
	release_region(card->port, AVMB1_PORTLEN);
	ctrl->driverdata = 0;
	kfree(card->ctrlinfo);
	kfree(card);

	MOD_DEC_USE_COUNT;
}

/* ------------------------------------------------------------- */

static char *b1pci_procinfo(struct capi_ctr *ctrl)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);

	if (!cinfo)
		return "";
	sprintf(cinfo->infobuf, "%s %s 0x%x %d r%d",
		cinfo->cardname[0] ? cinfo->cardname : "-",
		cinfo->version[VER_DRIVER] ? cinfo->version[VER_DRIVER] : "-",
		cinfo->card ? cinfo->card->port : 0x0,
		cinfo->card ? cinfo->card->irq : 0,
		cinfo->card ? cinfo->card->revision : 0
		);
	return cinfo->infobuf;
}

/* ------------------------------------------------------------- */

static int b1pci_add_card(struct capi_driver *driver, struct capicardparams *p)
{
	avmcard *card;
	avmctrl_info *cinfo;
	int retval;

	MOD_INC_USE_COUNT;

	card = (avmcard *) kmalloc(sizeof(avmcard), GFP_ATOMIC);

	if (!card) {
		printk(KERN_WARNING "%s: no memory.\n", driver->name);
	        MOD_DEC_USE_COUNT;
		return -ENOMEM;
	}
	memset(card, 0, sizeof(avmcard));
        cinfo = (avmctrl_info *) kmalloc(sizeof(avmctrl_info), GFP_ATOMIC);
	if (!cinfo) {
		printk(KERN_WARNING "%s: no memory.\n", driver->name);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -ENOMEM;
	}
	memset(cinfo, 0, sizeof(avmctrl_info));
	card->ctrlinfo = cinfo;
	cinfo->card = card;
	sprintf(card->name, "b1pci-%x", p->port);
	card->port = p->port;
	card->irq = p->irq;
	card->cardtype = avm_b1pci;

	if (check_region(card->port, AVMB1_PORTLEN)) {
		printk(KERN_WARNING
		       "%s: ports 0x%03x-0x%03x in use.\n",
		       driver->name, card->port, card->port + AVMB1_PORTLEN);
	        kfree(card->ctrlinfo);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EBUSY;
	}
	b1_reset(card->port);
	if ((retval = b1_detect(card->port, card->cardtype)) != 0) {
		printk(KERN_NOTICE "%s: NO card at 0x%x (%d)\n",
					driver->name, card->port, retval);
	        kfree(card->ctrlinfo);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EIO;
	}
	b1_reset(card->port);
	b1_getrevision(card);

	request_region(p->port, AVMB1_PORTLEN, card->name);

	retval = request_irq(card->irq, b1pci_interrupt, SA_SHIRQ, card->name, card);
	if (retval) {
		printk(KERN_ERR "%s: unable to get IRQ %d.\n",
				driver->name, card->irq);
		release_region(card->port, AVMB1_PORTLEN);
	        kfree(card->ctrlinfo);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EBUSY;
	}

	cinfo->capi_ctrl = di->attach_ctr(driver, card->name, cinfo);
	if (!cinfo->capi_ctrl) {
		printk(KERN_ERR "%s: attach controller failed.\n",
				driver->name);
		free_irq(card->irq, card);
		release_region(card->port, AVMB1_PORTLEN);
	        kfree(card->ctrlinfo);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EBUSY;
	}

	if (card->revision >= 4) {
		printk(KERN_INFO
			"%s: AVM B1 PCI V4 at i/o %#x, irq %d, revision %d (no dma)\n",
			driver->name, card->port, card->irq, card->revision);
	} else {
		printk(KERN_INFO
			"%s: AVM B1 PCI at i/o %#x, irq %d, revision %d\n",
			driver->name, card->port, card->irq, card->revision);
	}

	return 0;
}

/* ------------------------------------------------------------- */

static struct capi_driver b1pci_driver = {
    name: "b1pci",
    revision: "0.0",
    load_firmware: b1_load_firmware,
    reset_ctr: b1_reset_ctr,
    remove_ctr: b1pci_remove_ctr,
    register_appl: b1_register_appl,
    release_appl: b1_release_appl,
    send_message: b1_send_message,

    procinfo: b1pci_procinfo,
    ctr_read_proc: b1ctl_read_proc,
    driver_read_proc: 0,	/* use standard driver_read_proc */

    add_card: 0, /* no add_card function */
};

#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
/* ------------------------------------------------------------- */

static struct capi_driver_interface *div4;

/* ------------------------------------------------------------- */

static void b1pciv4_remove_ctr(struct capi_ctr *ctrl)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;

 	b1dma_reset(card);

	div4->detach_ctr(ctrl);
	free_irq(card->irq, card);
	iounmap(card->mbase);
	release_region(card->port, AVMB1_PORTLEN);
	ctrl->driverdata = 0;
	kfree(card->ctrlinfo);
	kfree(card->dma);
	kfree(card);

	MOD_DEC_USE_COUNT;
}

static char *b1pciv4_procinfo(struct capi_ctr *ctrl)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);

	if (!cinfo)
		return "";
	sprintf(cinfo->infobuf, "%s %s 0x%x %d 0x%lx r%d",
		cinfo->cardname[0] ? cinfo->cardname : "-",
		cinfo->version[VER_DRIVER] ? cinfo->version[VER_DRIVER] : "-",
		cinfo->card ? cinfo->card->port : 0x0,
		cinfo->card ? cinfo->card->irq : 0,
		cinfo->card ? cinfo->card->membase : 0,
		cinfo->card ? cinfo->card->revision : 0
		);
	return cinfo->infobuf;
}

/* ------------------------------------------------------------- */

static int b1pciv4_add_card(struct capi_driver *driver, struct capicardparams *p)
{
	avmcard *card;
	avmctrl_info *cinfo;
	int retval;

	MOD_INC_USE_COUNT;

	card = (avmcard *) kmalloc(sizeof(avmcard), GFP_ATOMIC);

	if (!card) {
		printk(KERN_WARNING "%s: no memory.\n", driver->name);
	        MOD_DEC_USE_COUNT;
		return -ENOMEM;
	}
	memset(card, 0, sizeof(avmcard));
	card->dma = (avmcard_dmainfo *) kmalloc(sizeof(avmcard_dmainfo), GFP_ATOMIC);
	if (!card->dma) {
		printk(KERN_WARNING "%s: no memory.\n", driver->name);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -ENOMEM;
	}
	memset(card->dma, 0, sizeof(avmcard_dmainfo));
        cinfo = (avmctrl_info *) kmalloc(sizeof(avmctrl_info), GFP_ATOMIC);
	if (!cinfo) {
		printk(KERN_WARNING "%s: no memory.\n", driver->name);
		kfree(card->dma);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -ENOMEM;
	}
	memset(cinfo, 0, sizeof(avmctrl_info));
	card->ctrlinfo = cinfo;
	cinfo->card = card;
	sprintf(card->name, "b1pciv4-%x", p->port);
	card->port = p->port;
	card->irq = p->irq;
	card->membase = p->membase;
	card->cardtype = avm_b1pci;

	if (check_region(card->port, AVMB1_PORTLEN)) {
		printk(KERN_WARNING
		       "%s: ports 0x%03x-0x%03x in use.\n",
		       driver->name, card->port, card->port + AVMB1_PORTLEN);
	        kfree(card->ctrlinfo);
		kfree(card->dma);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EBUSY;
	}

	card->mbase = ioremap_nocache(card->membase, 64);
	if (!card->mbase) {
		printk(KERN_NOTICE "%s: can't remap memory at 0x%lx\n",
					driver->name, card->membase);
	        kfree(card->ctrlinfo);
		kfree(card->dma);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EIO;
	}

	b1dma_reset(card);

	if ((retval = b1pciv4_detect(card)) != 0) {
		printk(KERN_NOTICE "%s: NO card at 0x%x (%d)\n",
					driver->name, card->port, retval);
                iounmap(card->mbase);
	        kfree(card->ctrlinfo);
		kfree(card->dma);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EIO;
	}
	b1dma_reset(card);
	b1_getrevision(card);

	request_region(p->port, AVMB1_PORTLEN, card->name);

	retval = request_irq(card->irq, b1dma_interrupt, SA_SHIRQ, card->name, card);
	if (retval) {
		printk(KERN_ERR "%s: unable to get IRQ %d.\n",
				driver->name, card->irq);
                iounmap(card->mbase);
		release_region(card->port, AVMB1_PORTLEN);
	        kfree(card->ctrlinfo);
		kfree(card->dma);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EBUSY;
	}

	cinfo->capi_ctrl = div4->attach_ctr(driver, card->name, cinfo);
	if (!cinfo->capi_ctrl) {
		printk(KERN_ERR "%s: attach controller failed.\n", driver->name);
                iounmap(card->mbase);
		free_irq(card->irq, card);
		release_region(card->port, AVMB1_PORTLEN);
	        kfree(card->ctrlinfo);
		kfree(card->dma);
		kfree(card);
	        MOD_DEC_USE_COUNT;
		return -EBUSY;
	}
	card->cardnr = cinfo->capi_ctrl->cnr;

	skb_queue_head_init(&card->dma->send_queue);

	printk(KERN_INFO
		"%s: AVM B1 PCI V4 at i/o %#x, irq %d, mem %#lx, revision %d (dma)\n",
		driver->name, card->port, card->irq,
		card->membase, card->revision);

	return 0;
}

/* ------------------------------------------------------------- */


static struct capi_driver b1pciv4_driver = {
    name: "b1pciv4",
    revision: "0.0",
    load_firmware: b1dma_load_firmware,
    reset_ctr: b1dma_reset_ctr,
    remove_ctr: b1pciv4_remove_ctr,
    register_appl: b1dma_register_appl,
    release_appl: b1dma_release_appl,
    send_message: b1dma_send_message,

    procinfo: b1pciv4_procinfo,
    ctr_read_proc: b1dmactl_read_proc,
    driver_read_proc: 0,	/* use standard driver_read_proc */

    add_card: 0, /* no add_card function */
};

#endif /* CONFIG_ISDN_DRV_AVMB1_B1PCIV4 */

static int ncards = 0;

static int add_card(struct pci_dev *dev)
{
	struct capi_driver *driver = &b1pci_driver;
	struct capicardparams param;
	int retval;

	if (pci_enable_device(dev) < 0) {
		printk(KERN_ERR "%s: failed to enable AVM-B1\n",
		       driver->name);
		return -ENODEV;
	}
	param.irq = dev->irq;

	if (pci_resource_start(dev, 2)) { /* B1 PCI V4 */
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
		driver = &b1pciv4_driver;

		pci_set_master(dev);
#endif
		param.membase = pci_resource_start(dev, 0);
		param.port = pci_resource_start(dev, 2);

		printk(KERN_INFO
		"%s: PCI BIOS reports AVM-B1 V4 at i/o %#x, irq %d, mem %#x\n",
		driver->name, param.port, param.irq, param.membase);
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
		retval = b1pciv4_add_card(driver, &param);
#else
		retval = b1pci_add_card(driver, &param);
#endif
		if (retval != 0) {
		        printk(KERN_ERR
			"%s: no AVM-B1 V4 at i/o %#x, irq %d, mem %#x detected\n",
			driver->name, param.port, param.irq, param.membase);
		}
	} else {
		param.membase = 0;
		param.port = pci_resource_start(dev, 1);

		printk(KERN_INFO
		"%s: PCI BIOS reports AVM-B1 at i/o %#x, irq %d\n",
		driver->name, param.port, param.irq);
		retval = b1pci_add_card(driver, &param);
		if (retval != 0) {
		        printk(KERN_ERR
			"%s: no AVM-B1 at i/o %#x, irq %d detected\n",
			driver->name, param.port, param.irq);
		}
	}
	return retval;
}

static int __init b1pci_init(void)
{
	struct capi_driver *driver = &b1pci_driver;
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
	struct capi_driver *driverv4 = &b1pciv4_driver;
#endif
	struct pci_dev *dev = NULL;
	char *p;

	MOD_INC_USE_COUNT;

	if ((p = strchr(revision, ':')) != 0 && p[1]) {
		strncpy(driver->revision, p + 2, sizeof(driver->revision));
		driver->revision[sizeof(driver->revision)-1] = 0;
		if ((p = strchr(driver->revision, '$')) != 0 && p > driver->revision)
			*(p-1) = 0;
	}
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
	if ((p = strchr(revision, ':')) != 0 && p[1]) {
		strncpy(driverv4->revision, p + 2, sizeof(driverv4->revision));
		driverv4->revision[sizeof(driverv4->revision)-1] = 0;
		if ((p = strchr(driverv4->revision, '$')) != 0 && p > driverv4->revision)
			*(p-1) = 0;
	}
#endif

	printk(KERN_INFO "%s: revision %s\n", driver->name, driver->revision);

        di = attach_capi_driver(driver);
	if (!di) {
		printk(KERN_ERR "%s: failed to attach capi_driver\n",
				driver->name);
		MOD_DEC_USE_COUNT;
		return -ENODEV;
	}

#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
	printk(KERN_INFO "%s: revision %s\n", driverv4->name, driverv4->revision);

        div4 = attach_capi_driver(driverv4);
	if (!div4) {
    		detach_capi_driver(driver);
		printk(KERN_ERR "%s: failed to attach capi_driver\n",
				driverv4->name);
		MOD_DEC_USE_COUNT;
		return -ENODEV;
	}
#endif

	while ((dev = pci_find_device(PCI_VENDOR_ID_AVM, PCI_DEVICE_ID_AVM_B1, dev))) {
		if (add_card(dev) == 0)
			ncards++;
	}
	if (ncards) {
		printk(KERN_INFO "%s: %d B1-PCI card(s) detected\n",
				driver->name, ncards);
		MOD_DEC_USE_COUNT;
		return 0;
	}
	printk(KERN_ERR "%s: NO B1-PCI card detected\n", driver->name);
	detach_capi_driver(driver);
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
	detach_capi_driver(driverv4);
#endif
	MOD_DEC_USE_COUNT;
	return -ENODEV;
}

static void __exit b1pci_exit(void)
{
    detach_capi_driver(&b1pci_driver);
#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
    detach_capi_driver(&b1pciv4_driver);
#endif
}

module_init(b1pci_init);
module_exit(b1pci_exit);
