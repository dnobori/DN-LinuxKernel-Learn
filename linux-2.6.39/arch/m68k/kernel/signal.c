#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "signal_mm.c"
#else
#include "signal_no.c"
#endif
