#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "kmap_mm.c"
#else
#include "kmap_no.c"
#endif
