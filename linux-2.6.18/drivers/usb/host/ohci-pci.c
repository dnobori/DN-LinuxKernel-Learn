#include "linux/autoconf.h"
/*
 * OHCI HCD (Host Controller Driver) for USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceforge.net>
 * 
 * [ Initialisation is based on Linus'  ]
 * [ uhci code and gregs ohci fragments ]
 * [ (C) Copyright 1999 Linus Torvalds  ]
 * [ (C) Copyright 1999 Gregory P. Smith]
 * 
 * PCI Bus Glue
 *
 * This file is licenced under the GPL.
 */
 
#ifndef CONFIG_PCI
#error "This file is PCI bus glue.  CONFIG_PCI must be defined."
#endif

/*-------------------------------------------------------------------------*/

static int
ohci_pci_reset (struct usb_hcd *hcd)
{
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci_hcd_init (ohci);
	return ohci_init (ohci);
}

static int __devinit
ohci_pci_start (struct usb_hcd *hcd)
{
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	int		ret;

	/* REVISIT this whole block should move to reset(), which handles
	 * all the other one-time init.
	 */
	if (hcd->self.controller) {
		struct pci_dev *pdev = to_pci_dev(hcd->self.controller);

		/* AMD 756, for most chips (early revs), corrupts register
		 * values on read ... so enable the vendor workaround.
		 */
		if (pdev->vendor == PCI_VENDOR_ID_AMD
				&& pdev->device == 0x740c) {
			ohci->flags = OHCI_QUIRK_AMD756;
			ohci_dbg (ohci, "AMD756 erratum 4 workaround\n");
			/* also erratum 10 (suspend/resume issues) */
			device_init_wakeup(&hcd->self.root_hub->dev, 0);
		}

		/* FIXME for some of the early AMD 760 southbridges, OHCI
		 * won't work at all.  blacklist them.
		 */

		/* Apple's OHCI driver has a lot of bizarre workarounds
		 * for this chip.  Evidently control and bulk lists
		 * can get confused.  (B&W G3 models, and ...)
		 */
		else if (pdev->vendor == PCI_VENDOR_ID_OPTI
				&& pdev->device == 0xc861) {
			ohci_dbg (ohci,
				"WARNING: OPTi workarounds unavailable\n");
		}

		/* Check for NSC87560. We have to look at the bridge (fn1) to
		 * identify the USB (fn2). This quirk might apply to more or
		 * even all NSC stuff.
		 */
		else if (pdev->vendor == PCI_VENDOR_ID_NS) {
			struct pci_dev	*b;

			b  = pci_find_slot (pdev->bus->number,
					PCI_DEVFN (PCI_SLOT (pdev->devfn), 1));
			if (b && b->device == PCI_DEVICE_ID_NS_87560_LIO
					&& b->vendor == PCI_VENDOR_ID_NS) {
				ohci->flags |= OHCI_QUIRK_SUPERIO;
				ohci_dbg (ohci, "Using NSC SuperIO setup\n");
			}
		}

		/* Check for Compaq's ZFMicro chipset, which needs short 
		 * delays before control or bulk queues get re-activated
		 * in finish_unlinks()
		 */
		else if (pdev->vendor == PCI_VENDOR_ID_COMPAQ
				&& pdev->device  == 0xa0f8) {
			ohci->flags |= OHCI_QUIRK_ZFMICRO;
			ohci_dbg (ohci,
				"enabled Compaq ZFMicro chipset quirk\n");
		}

		/* RWC may not be set for add-in PCI cards, since boot
		 * firmware probably ignored them.  This transfers PCI
		 * PM wakeup capabilities (once the PCI layer is fixed).
		 */
		if (device_may_wakeup(&pdev->dev))
			ohci->hc_control |= OHCI_CTRL_RWC;
	}

	/* NOTE: there may have already been a first reset, to
	 * keep bios/smm irqs from making trouble
	 */
	if ((ret = ohci_run (ohci)) < 0) {
		ohci_err (ohci, "can't start\n");
		ohci_stop (hcd);
		return ret;
	}
	return 0;
}

#ifdef	CONFIG_PM

static int ohci_pci_suspend (struct usb_hcd *hcd, pm_message_t message)
{
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	unsigned long	flags;
	int		rc = 0;

	/* Root hub was already suspended. Disable irq emission and
	 * mark HW unaccessible, bail out if RH has been resumed. Use
	 * the spinlock to properly synchronize with possible pending
	 * RH suspend or resume activity.
	 *
	 * This is still racy as hcd->state is manipulated outside of
	 * any locks =P But that will be a different fix.
	 */
	spin_lock_irqsave (&ohci->lock, flags);
	if (hcd->state != HC_STATE_SUSPENDED) {
		rc = -EINVAL;
		goto bail;
	}
	ohci_writel(ohci, OHCI_INTR_MIE, &ohci->regs->intrdisable);
	(void)ohci_readl(ohci, &ohci->regs->intrdisable);
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
 bail:
	spin_unlock_irqrestore (&ohci->lock, flags);

	return rc;
}


static int ohci_pci_resume (struct usb_hcd *hcd)
{
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	usb_hcd_resume_root_hub(hcd);
	return 0;
}

#endif	/* CONFIG_PM */


/*-------------------------------------------------------------------------*/

static const struct hc_driver ohci_pci_hc_driver = {
	.description =		hcd_name,
	.product_desc =		"OHCI Host Controller",
	.hcd_priv_size =	sizeof(struct ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_MEMORY | HCD_USB11,

	/*
	 * basic lifecycle operations
	 */
	.reset =		ohci_pci_reset,
	.start =		ohci_pci_start,
#ifdef	CONFIG_PM
	.suspend =		ohci_pci_suspend,
	.resume =		ohci_pci_resume,
#endif
	.stop =			ohci_stop,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoint_disable =	ohci_endpoint_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ohci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
#ifdef	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#endif
	.start_port_reset =	ohci_start_port_reset,
};

/*-------------------------------------------------------------------------*/


static const struct pci_device_id pci_ids [] = { {
	/* handle any USB OHCI controller */
	PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_OHCI, ~0),
	.driver_data =	(unsigned long) &ohci_pci_hc_driver,
	}, { /* end: all zeroes */ }
};
MODULE_DEVICE_TABLE (pci, pci_ids);

/* pci driver glue; this is a "new style" PCI driver module */
static struct pci_driver ohci_pci_driver = {
	.name =		(char *) hcd_name,
	.id_table =	pci_ids,

	.probe =	usb_hcd_pci_probe,
	.remove =	usb_hcd_pci_remove,

#ifdef	CONFIG_PM
	.suspend =	usb_hcd_pci_suspend,
	.resume =	usb_hcd_pci_resume,
#endif
};

 
static int __init ohci_hcd_pci_init (void) 
{
	printk (KERN_DEBUG "%s: " DRIVER_INFO " (PCI)\n", hcd_name);
	if (usb_disabled())
		return -ENODEV;

	pr_debug ("%s: block sizes: ed %Zd td %Zd\n", hcd_name,
		sizeof (struct ed), sizeof (struct td));
	return pci_register_driver (&ohci_pci_driver);
}
module_init (ohci_hcd_pci_init);

/*-------------------------------------------------------------------------*/

static void __exit ohci_hcd_pci_cleanup (void) 
{	
	pci_unregister_driver (&ohci_pci_driver);
}
module_exit (ohci_hcd_pci_cleanup);
