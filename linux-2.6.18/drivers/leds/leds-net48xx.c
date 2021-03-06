#include "linux/autoconf.h"
/*
 * LEDs driver for Soekris net48xx
 *
 * Copyright (C) 2006 Chris Boot <bootc@bootc.net>
 *
 * Based on leds-ams-delta.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/err.h>
#include <asm/io.h>
#include <linux/scx200_gpio.h>

#define DRVNAME "net48xx-led"
#define NET48XX_ERROR_LED_GPIO	20

static struct platform_device *pdev;

static void net48xx_error_led_set(struct led_classdev *led_cdev,
		enum led_brightness value)
{
	if (value)
		scx200_gpio_set_high(NET48XX_ERROR_LED_GPIO);
	else
		scx200_gpio_set_low(NET48XX_ERROR_LED_GPIO);
}

static struct led_classdev net48xx_error_led = {
	.name		= "net48xx:error",
	.brightness_set	= net48xx_error_led_set,
};

#ifdef CONFIG_PM
static int net48xx_led_suspend(struct platform_device *dev,
		pm_message_t state)
{
	led_classdev_suspend(&net48xx_error_led);
	return 0;
}

static int net48xx_led_resume(struct platform_device *dev)
{
	led_classdev_resume(&net48xx_error_led);
	return 0;
}
#else
#define net48xx_led_suspend NULL
#define net48xx_led_resume NULL
#endif

static int net48xx_led_probe(struct platform_device *pdev)
{
	return led_classdev_register(&pdev->dev, &net48xx_error_led);
}

static int net48xx_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&net48xx_error_led);
	return 0;
}

static struct platform_driver net48xx_led_driver = {
	.probe		= net48xx_led_probe,
	.remove		= net48xx_led_remove,
	.suspend	= net48xx_led_suspend,
	.resume		= net48xx_led_resume,
	.driver		= {
		.name		= DRVNAME,
		.owner		= THIS_MODULE,
	},
};

static int __init net48xx_led_init(void)
{
	int ret;

	if (!scx200_gpio_present()) {
		ret = -ENODEV;
		goto out;
	}

	ret = platform_driver_register(&net48xx_led_driver);
	if (ret < 0)
		goto out;

	pdev = platform_device_register_simple(DRVNAME, -1, NULL, 0);
	if (IS_ERR(pdev)) {
		ret = PTR_ERR(pdev);
		platform_driver_unregister(&net48xx_led_driver);
		goto out;
	}

out:
	return ret;
}

static void __exit net48xx_led_exit(void)
{
	platform_device_unregister(pdev);
	platform_driver_unregister(&net48xx_led_driver);
}

module_init(net48xx_led_init);
module_exit(net48xx_led_exit);

MODULE_AUTHOR("Chris Boot <bootc@bootc.net>");
MODULE_DESCRIPTION("Soekris net48xx LED driver");
MODULE_LICENSE("GPL");

