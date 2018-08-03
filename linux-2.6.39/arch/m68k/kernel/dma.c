#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "dma_mm.c"
#else
#include "dma_no.c"
#endif
