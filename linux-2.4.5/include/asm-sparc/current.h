#include "linux/autoconf.h"
#ifndef _SPARC_CURRENT_H
#define _SPARC_CURRENT_H

/* Sparc rules... */
register struct task_struct *current asm("g6");

#endif /* !(_SPARC_CURRENT_H) */
