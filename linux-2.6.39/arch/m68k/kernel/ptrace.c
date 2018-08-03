#include "linux/generated/autoconf.h"
#ifdef CONFIG_MMU
#include "ptrace_mm.c"
#else
#include "ptrace_no.c"
#endif
