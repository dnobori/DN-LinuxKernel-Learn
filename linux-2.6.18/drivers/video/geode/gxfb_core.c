#include "linux/autoconf.h"
/*
 * Geode GX framebuffer driver.
 *
 *   Copyright (C) 2006 Arcom Control Systems Ltd.
 *
 *   This program is free software; you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License as published by the
 *   Free Software Foundation; either version 2 of the License, or (at your
 *   option) any later version.
 *
 *
 * This driver assumes that the BIOS has created a virtual PCI device header
 * for the video device. The PCI header is assumed to contain the following
 * BARs:
 *
 *    BAR0 - framebuffer memory
 *    BAR1 - graphics processor registers
 *    BAR2 - display controller registers
 *    BAR3 - video processor and flat panel control registers.
 *
 * 16 MiB of framebuffer memory is assumed to be available.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/pci.h>

#include "geodefb.h"
#include "display_gx.h"
#include "video_gx.h"

static char mode_option[32] = "640x480-16@60";

/* Modes relevant to the GX (taken from modedb.c) */
static const struct fb_videomode __initdata gx_modedb[] = {
	/* 640x480-60 VESA */
	{ NULL, 60, 640, 480, 39682,  48, 16, 33, 10, 96, 2,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 640x480-75 VESA */
	{ NULL, 75, 640, 480, 31746, 120, 16, 16, 01, 64, 3,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 640x480-85 VESA */
	{ NULL, 85, 640, 480, 27777, 80, 56, 25, 01, 56, 3,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 800x600-60 VESA */
	{ NULL, 60, 800, 600, 25000, 88, 40, 23, 01, 128, 4,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 800x600-75 VESA */
	{ NULL, 75, 800, 600, 20202, 160, 16, 21, 01, 80, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 800x600-85 VESA */
	{ NULL, 85, 800, 600, 17761, 152, 32, 27, 01, 64, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1024x768-60 VESA */
	{ NULL, 60, 1024, 768, 15384, 160, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1024x768-75 VESA */
	{ NULL, 75, 1024, 768, 12690, 176, 16, 28, 1, 96, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1024x768-85 VESA */
	{ NULL, 85, 1024, 768, 10582, 208, 48, 36, 1, 96, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1280x960-60 VESA */
	{ NULL, 60, 1280, 960, 9259, 312, 96, 36, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1280x960-85 VESA */
	{ NULL, 85, 1280, 960, 6734, 224, 64, 47, 1, 160, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1280x1024-60 VESA */
	{ NULL, 60, 1280, 1024, 9259, 248, 48, 38, 1, 112, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1280x1024-75 VESA */
	{ NULL, 75, 1280, 1024, 7407, 248, 16, 38, 1, 144, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1280x1024-85 VESA */
	{ NULL, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1600x1200-60 VESA */
	{ NULL, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1600x1200-75 VESA */
	{ NULL, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
	/* 1600x1200-85 VESA */
	{ NULL, 85, 1600, 1200, 4357, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	  FB_VMODE_NONINTERLACED, FB_MODE_IS_VESA },
};

static int gxfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	if (var->xres > 1600 || var->yres > 1200)
		return -EINVAL;
	if ((var->xres > 1280 || var->yres > 1024) && var->bits_per_pixel > 16)
		return -EINVAL;

	if (var->bits_per_pixel == 32) {
		var->red.offset   = 16; var->red.length   = 8;
		var->green.offset =  8; var->green.length = 8;
		var->blue.offset  =  0; var->blue.length  = 8;
	} else if (var->bits_per_pixel == 16) {
		var->red.offset   = 11; var->red.length   = 5;
		var->green.offset =  5; var->green.length = 6;
		var->blue.offset  =  0; var->blue.length  = 5;
	} else if (var->bits_per_pixel == 8) {
		var->red.offset   = 0; var->red.length   = 8;
		var->green.offset = 0; var->green.length = 8;
		var->blue.offset  = 0; var->blue.length  = 8;
	} else
		return -EINVAL;
	var->transp.offset = 0; var->transp.length = 0;

	/* Enough video memory? */
	if (gx_line_delta(var->xres, var->bits_per_pixel) * var->yres > info->fix.smem_len)
		return -EINVAL;

	/* FIXME: Check timing parameters here? */

	return 0;
}

static int gxfb_set_par(struct fb_info *info)
{
	struct geodefb_par *par = info->par;

	if (info->var.bits_per_pixel > 8) {
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		fb_dealloc_cmap(&info->cmap);
	} else {
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		fb_alloc_cmap(&info->cmap, 1<<info->var.bits_per_pixel, 0);
	}

	info->fix.line_length = gx_line_delta(info->var.xres, info->var.bits_per_pixel);

	par->dc_ops->set_mode(info);

	return 0;
}

static inline u_int chan_to_field(u_int chan, struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}

static int gxfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	struct geodefb_par *par = info->par;

	if (info->var.grayscale) {
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}

	/* Truecolor has hardware independent palette */
	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 *pal = info->pseudo_palette;
		u32 v;

		if (regno >= 16)
			return -EINVAL;

		v  = chan_to_field(red, &info->var.red);
		v |= chan_to_field(green, &info->var.green);
		v |= chan_to_field(blue, &info->var.blue);

		pal[regno] = v;
	} else {
		if (regno >= 256)
			return -EINVAL;

		par->dc_ops->set_palette_reg(info, regno, red, green, blue);
	}

	return 0;
}

static int gxfb_blank(int blank_mode, struct fb_info *info)
{
	struct geodefb_par *par = info->par;

	return par->vid_ops->blank_display(info, blank_mode);
}

static int __init gxfb_map_video_memory(struct fb_info *info, struct pci_dev *dev)
{
	struct geodefb_par *par = info->par;
	int fb_len;
	int ret;

	ret = pci_enable_device(dev);
	if (ret < 0)
		return ret;

	ret = pci_request_region(dev, 3, "gxfb (video processor)");
	if (ret < 0)
		return ret;
	par->vid_regs = ioremap(pci_resource_start(dev, 3),
				pci_resource_len(dev, 3));
	if (!par->vid_regs)
		return -ENOMEM;

	ret = pci_request_region(dev, 2, "gxfb (display controller)");
	if (ret < 0)
		return ret;
	par->dc_regs = ioremap(pci_resource_start(dev, 2), pci_resource_len(dev, 2));
	if (!par->dc_regs)
		return -ENOMEM;

	ret = pci_request_region(dev, 0, "gxfb (framebuffer)");
	if (ret < 0)
		return ret;
	if ((fb_len = gx_frame_buffer_size()) < 0)
		return -ENOMEM;
	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = fb_len;
	info->screen_base = ioremap(info->fix.smem_start, info->fix.smem_len);
	if (!info->screen_base)
		return -ENOMEM;

	dev_info(&dev->dev, "%d Kibyte of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	return 0;
}

static struct fb_ops gxfb_ops = {
	.owner		= THIS_MODULE,
	.fb_check_var	= gxfb_check_var,
	.fb_set_par	= gxfb_set_par,
	.fb_setcolreg	= gxfb_setcolreg,
	.fb_blank       = gxfb_blank,
	/* No HW acceleration for now. */
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};

static struct fb_info * __init gxfb_init_fbinfo(struct device *dev)
{
	struct geodefb_par *par;
	struct fb_info *info;

	/* Alloc enough space for the pseudo palette. */
	info = framebuffer_alloc(sizeof(struct geodefb_par) + sizeof(u32) * 16, dev);
	if (!info)
		return NULL;

	par = info->par;

	strcpy(info->fix.id, "Geode GX");

	info->fix.type		= FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux	= 0;
	info->fix.xpanstep	= 0;
	info->fix.ypanstep	= 0;
	info->fix.ywrapstep	= 0;
	info->fix.accel		= FB_ACCEL_NONE;

	info->var.nonstd	= 0;
	info->var.activate	= FB_ACTIVATE_NOW;
	info->var.height	= -1;
	info->var.width	= -1;
	info->var.accel_flags = 0;
	info->var.vmode	= FB_VMODE_NONINTERLACED;

	info->fbops		= &gxfb_ops;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;

	info->pseudo_palette	= (void *)par + sizeof(struct geodefb_par);

	info->var.grayscale	= 0;

	return info;
}

static int __init gxfb_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct geodefb_par *par;
	struct fb_info *info;
	int ret;

	info = gxfb_init_fbinfo(&pdev->dev);
	if (!info)
		return -ENOMEM;
	par = info->par;

	/* GX display controller and GX video device. */
	par->dc_ops  = &gx_dc_ops;
	par->vid_ops = &gx_vid_ops;

	if ((ret = gxfb_map_video_memory(info, pdev)) < 0) {
		dev_err(&pdev->dev, "failed to map frame buffer or controller registers\n");
		goto err;
	}

	ret = fb_find_mode(&info->var, info, mode_option,
			   gx_modedb, ARRAY_SIZE(gx_modedb), NULL, 16);
	if (ret == 0 || ret == 4) {
		dev_err(&pdev->dev, "could not find valid video mode\n");
		ret = -EINVAL;
		goto err;
	}

        /* Clear the frame buffer of garbage. */
        memset_io(info->screen_base, 0, info->fix.smem_len);

	gxfb_check_var(&info->var, info);
	gxfb_set_par(info);

	if (register_framebuffer(info) < 0) {
		ret = -EINVAL;
		goto err;
	}
	pci_set_drvdata(pdev, info);
	printk(KERN_INFO "fb%d: %s frame buffer device\n", info->node, info->fix.id);
	return 0;

  err:
	if (info->screen_base) {
		iounmap(info->screen_base);
		pci_release_region(pdev, 0);
	}
	if (par->vid_regs) {
		iounmap(par->vid_regs);
		pci_release_region(pdev, 3);
	}
	if (par->dc_regs) {
		iounmap(par->dc_regs);
		pci_release_region(pdev, 2);
	}

	if (info)
		framebuffer_release(info);
	return ret;
}

static void gxfb_remove(struct pci_dev *pdev)
{
	struct fb_info *info = pci_get_drvdata(pdev);
	struct geodefb_par *par = info->par;

	unregister_framebuffer(info);

	iounmap((void __iomem *)info->screen_base);
	pci_release_region(pdev, 0);

	iounmap(par->vid_regs);
	pci_release_region(pdev, 3);

	iounmap(par->dc_regs);
	pci_release_region(pdev, 2);

	pci_set_drvdata(pdev, NULL);

	framebuffer_release(info);
}

static struct pci_device_id gxfb_id_table[] = {
	{ PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_CS5535_VIDEO,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY << 16,
	  0xff0000, 0 },
	{ 0, }
};

MODULE_DEVICE_TABLE(pci, gxfb_id_table);

static struct pci_driver gxfb_driver = {
	.name		= "gxfb",
	.id_table	= gxfb_id_table,
	.probe		= gxfb_probe,
	.remove		= gxfb_remove,
};

static int __init gxfb_init(void)
{
#ifndef MODULE
	if (fb_get_options("gxfb", NULL))
		return -ENODEV;
#endif
	return pci_register_driver(&gxfb_driver);
}

static void __exit gxfb_cleanup(void)
{
	pci_unregister_driver(&gxfb_driver);
}

module_init(gxfb_init);
module_exit(gxfb_cleanup);

module_param_string(mode, mode_option, sizeof(mode_option), 0444);
MODULE_PARM_DESC(mode, "video mode (<x>x<y>[-<bpp>][@<refr>])");

MODULE_DESCRIPTION("Framebuffer driver for the AMD Geode GX");
MODULE_LICENSE("GPL");
