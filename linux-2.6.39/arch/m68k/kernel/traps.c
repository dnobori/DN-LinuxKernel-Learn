#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "traps_mm.c"
#else
#include "traps_no.c"
#endif
