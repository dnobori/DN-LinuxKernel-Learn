#include "linux/generated/autoconf.h"
/*
 * ADE7758 Polyphase Multifunction Energy Metering IC Driver
 *
 * Copyright 2010 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/list.h>

#include "../iio.h"
#include "../sysfs.h"
#include "meter.h"
#include "ade7758.h"

int ade7758_spi_write_reg_8(struct device *dev,
		u8 reg_address,
		u8 val)
{
	int ret;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7758_WRITE_REG(reg_address);
	st->tx[1] = val;

	ret = spi_write(st->us, st->tx, 2);
	mutex_unlock(&st->buf_lock);

	return ret;
}

static int ade7758_spi_write_reg_16(struct device *dev,
		u8 reg_address,
		u16 value)
{
	int ret;
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);
	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.bits_per_word = 8,
			.len = 3,
		}
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7758_WRITE_REG(reg_address);
	st->tx[1] = (value >> 8) & 0xFF;
	st->tx[2] = value & 0xFF;

	spi_message_init(&msg);
	spi_message_add_tail(xfers, &msg);
	ret = spi_sync(st->us, &msg);
	mutex_unlock(&st->buf_lock);

	return ret;
}

static int ade7758_spi_write_reg_24(struct device *dev,
		u8 reg_address,
		u32 value)
{
	int ret;
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);
	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.bits_per_word = 8,
			.len = 4,
		}
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7758_WRITE_REG(reg_address);
	st->tx[1] = (value >> 16) & 0xFF;
	st->tx[2] = (value >> 8) & 0xFF;
	st->tx[3] = value & 0xFF;

	spi_message_init(&msg);
	spi_message_add_tail(xfers, &msg);
	ret = spi_sync(st->us, &msg);
	mutex_unlock(&st->buf_lock);

	return ret;
}

static int ade7758_spi_read_reg_8(struct device *dev,
		u8 reg_address,
		u8 *val)
{
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.rx_buf = st->rx,
			.bits_per_word = 8,
			.len = 2,
		},
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7758_READ_REG(reg_address);
	st->tx[1] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(xfers, &msg);
	ret = spi_sync(st->us, &msg);
	if (ret) {
		dev_err(&st->us->dev, "problem when reading 8 bit register 0x%02X",
				reg_address);
		goto error_ret;
	}
	*val = st->rx[1];

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}

static int ade7758_spi_read_reg_16(struct device *dev,
		u8 reg_address,
		u16 *val)
{
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.rx_buf = st->rx,
			.bits_per_word = 8,
			.len = 3,
		},
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7758_READ_REG(reg_address);
	st->tx[1] = 0;
	st->tx[2] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(xfers, &msg);
	ret = spi_sync(st->us, &msg);
	if (ret) {
		dev_err(&st->us->dev, "problem when reading 16 bit register 0x%02X",
				reg_address);
		goto error_ret;
	}
	*val = (st->rx[1] << 8) | st->rx[2];

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}

static int ade7758_spi_read_reg_24(struct device *dev,
		u8 reg_address,
		u32 *val)
{
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.rx_buf = st->rx,
			.bits_per_word = 8,
			.len = 4,
		},
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7758_READ_REG(reg_address);
	st->tx[1] = 0;
	st->tx[2] = 0;
	st->tx[3] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(xfers, &msg);
	ret = spi_sync(st->us, &msg);
	if (ret) {
		dev_err(&st->us->dev, "problem when reading 24 bit register 0x%02X",
				reg_address);
		goto error_ret;
	}
	*val = (st->rx[1] << 16) | (st->rx[2] << 8) | st->rx[3];

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}

static ssize_t ade7758_read_8bit(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	int ret;
	u8 val = 0;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = ade7758_spi_read_reg_8(dev, this_attr->address, &val);
	if (ret)
		return ret;

	return sprintf(buf, "%u\n", val);
}

static ssize_t ade7758_read_16bit(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	int ret;
	u16 val = 0;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = ade7758_spi_read_reg_16(dev, this_attr->address, &val);
	if (ret)
		return ret;

	return sprintf(buf, "%u\n", val);
}

static ssize_t ade7758_read_24bit(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	int ret;
	u32 val = 0;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = ade7758_spi_read_reg_24(dev, this_attr->address, &val);
	if (ret)
		return ret;

	return sprintf(buf, "%u\n", val & 0xFFFFFF);
}

static ssize_t ade7758_write_8bit(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t len)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret;
	long val;

	ret = strict_strtol(buf, 10, &val);
	if (ret)
		goto error_ret;
	ret = ade7758_spi_write_reg_8(dev, this_attr->address, val);

error_ret:
	return ret ? ret : len;
}

static ssize_t ade7758_write_16bit(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t len)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret;
	long val;

	ret = strict_strtol(buf, 10, &val);
	if (ret)
		goto error_ret;
	ret = ade7758_spi_write_reg_16(dev, this_attr->address, val);

error_ret:
	return ret ? ret : len;
}

int ade7758_reset(struct device *dev)
{
	int ret;
	u8 val;
	ade7758_spi_read_reg_8(dev,
			ADE7758_OPMODE,
			&val);
	val |= 1 << 6; /* Software Chip Reset */
	ret = ade7758_spi_write_reg_8(dev,
			ADE7758_OPMODE,
			val);

	return ret;
}

static ssize_t ade7758_write_reset(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t len)
{
	if (len < 1)
		return -1;
	switch (buf[0]) {
	case '1':
	case 'y':
	case 'Y':
		return ade7758_reset(dev);
	}
	return -1;
}

static IIO_DEV_ATTR_VPEAK(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_VPEAK);
static IIO_DEV_ATTR_IPEAK(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_VPEAK);
static IIO_DEV_ATTR_APHCAL(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_APHCAL);
static IIO_DEV_ATTR_BPHCAL(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_BPHCAL);
static IIO_DEV_ATTR_CPHCAL(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_CPHCAL);
static IIO_DEV_ATTR_WDIV(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_WDIV);
static IIO_DEV_ATTR_VADIV(S_IWUSR | S_IRUGO,
		ade7758_read_8bit,
		ade7758_write_8bit,
		ADE7758_VADIV);
static IIO_DEV_ATTR_AIRMS(S_IRUGO,
		ade7758_read_24bit,
		NULL,
		ADE7758_AIRMS);
static IIO_DEV_ATTR_BIRMS(S_IRUGO,
		ade7758_read_24bit,
		NULL,
		ADE7758_BIRMS);
static IIO_DEV_ATTR_CIRMS(S_IRUGO,
		ade7758_read_24bit,
		NULL,
		ADE7758_CIRMS);
static IIO_DEV_ATTR_AVRMS(S_IRUGO,
		ade7758_read_24bit,
		NULL,
		ADE7758_AVRMS);
static IIO_DEV_ATTR_BVRMS(S_IRUGO,
		ade7758_read_24bit,
		NULL,
		ADE7758_BVRMS);
static IIO_DEV_ATTR_CVRMS(S_IRUGO,
		ade7758_read_24bit,
		NULL,
		ADE7758_CVRMS);
static IIO_DEV_ATTR_AIRMSOS(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_AIRMSOS);
static IIO_DEV_ATTR_BIRMSOS(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_BIRMSOS);
static IIO_DEV_ATTR_CIRMSOS(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_CIRMSOS);
static IIO_DEV_ATTR_AVRMSOS(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_AVRMSOS);
static IIO_DEV_ATTR_BVRMSOS(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_BVRMSOS);
static IIO_DEV_ATTR_CVRMSOS(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_CVRMSOS);
static IIO_DEV_ATTR_AIGAIN(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_AIGAIN);
static IIO_DEV_ATTR_BIGAIN(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_BIGAIN);
static IIO_DEV_ATTR_CIGAIN(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_CIGAIN);
static IIO_DEV_ATTR_AVRMSGAIN(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_AVRMSGAIN);
static IIO_DEV_ATTR_BVRMSGAIN(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_BVRMSGAIN);
static IIO_DEV_ATTR_CVRMSGAIN(S_IWUSR | S_IRUGO,
		ade7758_read_16bit,
		ade7758_write_16bit,
		ADE7758_CVRMSGAIN);

int ade7758_set_irq(struct device *dev, bool enable)
{
	int ret;
	u32 irqen;
	ret = ade7758_spi_read_reg_24(dev, ADE7758_MASK, &irqen);
	if (ret)
		goto error_ret;

	if (enable)
		irqen |= 1 << 16; /* Enables an interrupt when a data is
				     present in the waveform register */
	else
		irqen &= ~(1 << 16);

	ret = ade7758_spi_write_reg_24(dev, ADE7758_MASK, irqen);
	if (ret)
		goto error_ret;

error_ret:
	return ret;
}

/* Power down the device */
static int ade7758_stop_device(struct device *dev)
{
	int ret;
	u8 val;
	ade7758_spi_read_reg_8(dev,
			ADE7758_OPMODE,
			&val);
	val |= 7 << 3;  /* ADE7758 powered down */
	ret = ade7758_spi_write_reg_8(dev,
			ADE7758_OPMODE,
			val);

	return ret;
}

static int ade7758_initial_setup(struct ade7758_state *st)
{
	int ret;
	struct device *dev = &st->indio_dev->dev;

	/* use low spi speed for init */
	st->us->mode = SPI_MODE_3;
	spi_setup(st->us);

	/* Disable IRQ */
	ret = ade7758_set_irq(dev, false);
	if (ret) {
		dev_err(dev, "disable irq failed");
		goto err_ret;
	}

	ade7758_reset(dev);
	msleep(ADE7758_STARTUP_DELAY);

err_ret:
	return ret;
}

static ssize_t ade7758_read_frequency(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	int ret, len = 0;
	u8 t;
	int sps;
	ret = ade7758_spi_read_reg_8(dev,
			ADE7758_WAVMODE,
			&t);
	if (ret)
		return ret;

	t = (t >> 5) & 0x3;
	sps = 26040 / (1 << t);

	len = sprintf(buf, "%d SPS\n", sps);
	return len;
}

static ssize_t ade7758_write_frequency(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t len)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ade7758_state *st = iio_dev_get_devdata(indio_dev);
	unsigned long val;
	int ret;
	u8 reg, t;

	ret = strict_strtol(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&indio_dev->mlock);

	t = (26040 / val);
	if (t > 0)
		t >>= 1;

	if (t > 1)
		st->us->max_speed_hz = ADE7758_SPI_SLOW;
	else
		st->us->max_speed_hz = ADE7758_SPI_FAST;

	ret = ade7758_spi_read_reg_8(dev,
			ADE7758_WAVMODE,
			&reg);
	if (ret)
		goto out;

	reg &= ~(5 << 3);
	reg |= t << 5;

	ret = ade7758_spi_write_reg_8(dev,
			ADE7758_WAVMODE,
			reg);

out:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}

static ssize_t ade7758_read_waveform_type(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	int ret, len = 0;
	u8 t;
	ret = ade7758_spi_read_reg_8(dev,
			ADE7758_WAVMODE,
			&t);
	if (ret)
		return ret;

	t = (t >> 2) & 0x7;

	len = sprintf(buf, "%d\n", t);

	return len;
}

static ssize_t ade7758_write_waveform_type(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t len)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	unsigned long val;
	int ret;
	u8 reg;

	ret = strict_strtol(buf, 10, &val);
	if (ret)
		return ret;

	if (val > 4)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);

	ret = ade7758_spi_read_reg_8(dev,
			ADE7758_WAVMODE,
			&reg);
	if (ret)
		goto out;

	reg &= ~(7 << 2);
	reg |= val << 2;

	ret = ade7758_spi_write_reg_8(dev,
			ADE7758_WAVMODE,
			reg);

out:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}

static IIO_DEV_ATTR_TEMP_RAW(ade7758_read_8bit);
static IIO_CONST_ATTR(temp_offset, "129 C");
static IIO_CONST_ATTR(temp_scale, "4 C");

static IIO_DEV_ATTR_AWATTHR(ade7758_read_16bit,
		ADE7758_AWATTHR);
static IIO_DEV_ATTR_BWATTHR(ade7758_read_16bit,
		ADE7758_BWATTHR);
static IIO_DEV_ATTR_CWATTHR(ade7758_read_16bit,
		ADE7758_CWATTHR);
static IIO_DEV_ATTR_AVARHR(ade7758_read_16bit,
		ADE7758_AVARHR);
static IIO_DEV_ATTR_BVARHR(ade7758_read_16bit,
		ADE7758_BVARHR);
static IIO_DEV_ATTR_CVARHR(ade7758_read_16bit,
		ADE7758_CVARHR);
static IIO_DEV_ATTR_AVAHR(ade7758_read_16bit,
		ADE7758_AVAHR);
static IIO_DEV_ATTR_BVAHR(ade7758_read_16bit,
		ADE7758_BVAHR);
static IIO_DEV_ATTR_CVAHR(ade7758_read_16bit,
		ADE7758_CVAHR);

static IIO_DEV_ATTR_SAMP_FREQ(S_IWUSR | S_IRUGO,
		ade7758_read_frequency,
		ade7758_write_frequency);

/**
 * IIO_DEV_ATTR_WAVEFORM_TYPE - set the type of waveform.
 * @_mode: sysfs file mode/permissions
 * @_show: output method for the attribute
 * @_store: input method for the attribute
 **/
#define IIO_DEV_ATTR_WAVEFORM_TYPE(_mode, _show, _store)			\
	IIO_DEVICE_ATTR(waveform_type, _mode, _show, _store, 0)

static IIO_DEV_ATTR_WAVEFORM_TYPE(S_IWUSR | S_IRUGO,
		ade7758_read_waveform_type,
		ade7758_write_waveform_type);

static IIO_DEV_ATTR_RESET(ade7758_write_reset);

static IIO_CONST_ATTR_SAMP_FREQ_AVAIL("26000 13000 65000 33000");

static IIO_CONST_ATTR(name, "ade7758");

static struct attribute *ade7758_event_attributes[] = {
	NULL
};

static struct attribute_group ade7758_event_attribute_group = {
	.attrs = ade7758_event_attributes,
};

static struct attribute *ade7758_attributes[] = {
	&iio_dev_attr_temp_raw.dev_attr.attr,
	&iio_const_attr_temp_offset.dev_attr.attr,
	&iio_const_attr_temp_scale.dev_attr.attr,
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
	&iio_dev_attr_waveform_type.dev_attr.attr,
	&iio_const_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_reset.dev_attr.attr,
	&iio_const_attr_name.dev_attr.attr,
	&iio_dev_attr_awatthr.dev_attr.attr,
	&iio_dev_attr_bwatthr.dev_attr.attr,
	&iio_dev_attr_cwatthr.dev_attr.attr,
	&iio_dev_attr_avarhr.dev_attr.attr,
	&iio_dev_attr_bvarhr.dev_attr.attr,
	&iio_dev_attr_cvarhr.dev_attr.attr,
	&iio_dev_attr_avahr.dev_attr.attr,
	&iio_dev_attr_bvahr.dev_attr.attr,
	&iio_dev_attr_cvahr.dev_attr.attr,
	&iio_dev_attr_vpeak.dev_attr.attr,
	&iio_dev_attr_ipeak.dev_attr.attr,
	&iio_dev_attr_aphcal.dev_attr.attr,
	&iio_dev_attr_bphcal.dev_attr.attr,
	&iio_dev_attr_cphcal.dev_attr.attr,
	&iio_dev_attr_wdiv.dev_attr.attr,
	&iio_dev_attr_vadiv.dev_attr.attr,
	&iio_dev_attr_airms.dev_attr.attr,
	&iio_dev_attr_birms.dev_attr.attr,
	&iio_dev_attr_cirms.dev_attr.attr,
	&iio_dev_attr_avrms.dev_attr.attr,
	&iio_dev_attr_bvrms.dev_attr.attr,
	&iio_dev_attr_cvrms.dev_attr.attr,
	&iio_dev_attr_aigain.dev_attr.attr,
	&iio_dev_attr_bigain.dev_attr.attr,
	&iio_dev_attr_cigain.dev_attr.attr,
	&iio_dev_attr_avrmsgain.dev_attr.attr,
	&iio_dev_attr_bvrmsgain.dev_attr.attr,
	&iio_dev_attr_cvrmsgain.dev_attr.attr,
	&iio_dev_attr_airmsos.dev_attr.attr,
	&iio_dev_attr_birmsos.dev_attr.attr,
	&iio_dev_attr_cirmsos.dev_attr.attr,
	&iio_dev_attr_avrmsos.dev_attr.attr,
	&iio_dev_attr_bvrmsos.dev_attr.attr,
	&iio_dev_attr_cvrmsos.dev_attr.attr,
	NULL,
};

static const struct attribute_group ade7758_attribute_group = {
	.attrs = ade7758_attributes,
};



static int __devinit ade7758_probe(struct spi_device *spi)
{
	int ret, regdone = 0;
	struct ade7758_state *st = kzalloc(sizeof *st, GFP_KERNEL);
	if (!st) {
		ret =  -ENOMEM;
		goto error_ret;
	}
	/* this is only used for removal purposes */
	spi_set_drvdata(spi, st);

	/* Allocate the comms buffers */
	st->rx = kzalloc(sizeof(*st->rx)*ADE7758_MAX_RX, GFP_KERNEL);
	if (st->rx == NULL) {
		ret = -ENOMEM;
		goto error_free_st;
	}
	st->tx = kzalloc(sizeof(*st->tx)*ADE7758_MAX_TX, GFP_KERNEL);
	if (st->tx == NULL) {
		ret = -ENOMEM;
		goto error_free_rx;
	}
	st->us = spi;
	mutex_init(&st->buf_lock);
	/* setup the industrialio driver allocated elements */
	st->indio_dev = iio_allocate_device();
	if (st->indio_dev == NULL) {
		ret = -ENOMEM;
		goto error_free_tx;
	}

	st->indio_dev->dev.parent = &spi->dev;
	st->indio_dev->num_interrupt_lines = 1;
	st->indio_dev->event_attrs = &ade7758_event_attribute_group;
	st->indio_dev->attrs = &ade7758_attribute_group;
	st->indio_dev->dev_data = (void *)(st);
	st->indio_dev->driver_module = THIS_MODULE;
	st->indio_dev->modes = INDIO_DIRECT_MODE;

	ret = ade7758_configure_ring(st->indio_dev);
	if (ret)
		goto error_free_dev;

	ret = iio_device_register(st->indio_dev);
	if (ret)
		goto error_unreg_ring_funcs;
	regdone = 1;

	ret = ade7758_initialize_ring(st->indio_dev->ring);
	if (ret) {
		printk(KERN_ERR "failed to initialize the ring\n");
		goto error_unreg_ring_funcs;
	}

	if (spi->irq) {
		ret = iio_register_interrupt_line(spi->irq,
				st->indio_dev,
				0,
				IRQF_TRIGGER_FALLING,
				"ade7758");
		if (ret)
			goto error_uninitialize_ring;

		ret = ade7758_probe_trigger(st->indio_dev);
		if (ret)
			goto error_unregister_line;
	}

	/* Get the device into a sane initial state */
	ret = ade7758_initial_setup(st);
	if (ret)
		goto error_remove_trigger;
	return 0;

error_remove_trigger:
	if (st->indio_dev->modes & INDIO_RING_TRIGGERED)
		ade7758_remove_trigger(st->indio_dev);
error_unregister_line:
	if (st->indio_dev->modes & INDIO_RING_TRIGGERED)
		iio_unregister_interrupt_line(st->indio_dev, 0);
error_uninitialize_ring:
	ade7758_uninitialize_ring(st->indio_dev->ring);
error_unreg_ring_funcs:
	ade7758_unconfigure_ring(st->indio_dev);
error_free_dev:
	if (regdone)
		iio_device_unregister(st->indio_dev);
	else
		iio_free_device(st->indio_dev);
error_free_tx:
	kfree(st->tx);
error_free_rx:
	kfree(st->rx);
error_free_st:
	kfree(st);
error_ret:
	return ret;
}

static int ade7758_remove(struct spi_device *spi)
{
	int ret;
	struct ade7758_state *st = spi_get_drvdata(spi);
	struct iio_dev *indio_dev = st->indio_dev;

	ret = ade7758_stop_device(&(indio_dev->dev));
	if (ret)
		goto err_ret;

	flush_scheduled_work();

	ade7758_remove_trigger(indio_dev);
	if (spi->irq && gpio_is_valid(irq_to_gpio(spi->irq)) > 0)
		iio_unregister_interrupt_line(indio_dev, 0);

	ade7758_uninitialize_ring(indio_dev->ring);
	iio_device_unregister(indio_dev);
	ade7758_unconfigure_ring(indio_dev);
	kfree(st->tx);
	kfree(st->rx);
	kfree(st);

	return 0;

err_ret:
	return ret;
}

static struct spi_driver ade7758_driver = {
	.driver = {
		.name = "ade7758",
		.owner = THIS_MODULE,
	},
	.probe = ade7758_probe,
	.remove = __devexit_p(ade7758_remove),
};

static __init int ade7758_init(void)
{
	return spi_register_driver(&ade7758_driver);
}
module_init(ade7758_init);

static __exit void ade7758_exit(void)
{
	spi_unregister_driver(&ade7758_driver);
}
module_exit(ade7758_exit);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADE7758 Polyphase Multifunction Energy Metering IC Driver");
MODULE_LICENSE("GPL v2");
