#
# drivers/scsi/aic7xxx/Makefile
#
# Makefile for the Linux aic7xxx SCSI driver.
#

O_TARGET := aic7xxx_drv.o

list-multi	:= aic7xxx_mod.o

obj-$(CONFIG_SCSI_AIC7XXX)	+= aic7xxx_mod.o

# Platform Specific Files
AIC7XXX_OBJS = aic7xxx_linux.o aic7xxx_linux_pci.o
AIC7XXX_OBJS += aic7xxx_proc.o aic7770_linux.o
# Core Files
AIC7XXX_OBJS += aic7xxx.o aic7xxx_pci.o aic7xxx_93cx6.o aic7770.o

# Override our module desitnation
MOD_DESTDIR = $(shell cd .. && $(CONFIG_SHELL) $(TOPDIR)/scripts/pathdown.sh)
MOD_TARGET = aic7xxx.o

include $(TOPDIR)/Rules.make

aic7xxx_mod.o: aic7xxx_seq.h aic7xxx_reg.h $(AIC7XXX_OBJS)
	$(LD) $(LD_RFLAG) -r -o $@ $(AIC7XXX_OBJS)

ifeq ($(CONFIG_AIC7XXX_BUILD_FIRMWARE),y)
aic7xxx_seq.h aic7xxx_reg.h: aic7xxx.seq aic7xxx.reg aicasm/aicasm
	aicasm/aicasm -I. -r aic7xxx_reg.h -o aic7xxx_seq.h aic7xxx.seq
else
aic7xxx_seq.h aic7xxx_reg.h: aic7xxx.seq aic7xxx.reg
	echo "Warning, generated aic7xxx firmware files may be out of date!\n"
endif

aicasm/aicasm: aicasm/*.[chyl]
	$(MAKE) -C aicasm
