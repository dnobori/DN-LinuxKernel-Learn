#include "linux/autoconf.h"
#undef LOCK
#define LOCK		WSL

#undef UNLOCK
#define UNLOCK		WSU

#undef RLOCK
#define RLOCK		RSL

#undef WLOCK
#define WLOCK		WSL

#undef INIT
#define INIT		RWSI