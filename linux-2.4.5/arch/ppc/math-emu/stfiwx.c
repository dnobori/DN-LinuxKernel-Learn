#include "linux/autoconf.h"
/*
 * BK Id: SCCS/s.stfiwx.c 1.6 05/17/01 18:14:23 cort
 */
#include <linux/types.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

int
stfiwx(u32 *frS, void *ea)
{
#ifdef DEBUG
	printk("%s: %p %p\n", __FUNCTION__, frS, ea);
#endif

	if (copy_to_user(ea, &frS[1], sizeof(frS[1])))
		return -EFAULT;

	return 0;
}