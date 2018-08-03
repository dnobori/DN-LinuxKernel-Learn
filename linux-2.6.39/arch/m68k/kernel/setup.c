#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "setup_mm.c"
#else
#include "setup_no.c"
#endif
