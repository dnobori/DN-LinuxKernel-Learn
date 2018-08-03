#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "process_mm.c"
#else
#include "process_no.c"
#endif
