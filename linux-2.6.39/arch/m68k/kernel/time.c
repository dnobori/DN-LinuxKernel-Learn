#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "time_mm.c"
#else
#include "time_no.c"
#endif
