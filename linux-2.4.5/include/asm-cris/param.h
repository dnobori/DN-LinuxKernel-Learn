#include "linux/autoconf.h"
#ifndef _ASMCRIS_PARAM_H
#define _ASMCRIS_PARAM_H

#ifndef HZ
#define HZ 100
#endif

#define EXEC_PAGESIZE	8192

#ifndef NGROUPS
#define NGROUPS		32
#endif

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN	64	/* max length of hostname */

#ifdef __KERNEL__
# define CLOCKS_PER_SEC        100     /* frequency at which times() counts */
#endif

#endif
