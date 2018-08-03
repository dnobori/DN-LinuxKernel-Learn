#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "module_mm.c"
#else
#include "module_no.c"
#endif
