cmd_scripts/genksyms/parse.o := gcc -Wp,-MD,scripts/genksyms/.parse.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer    -Wno-uninitialized -Iscripts/genksyms -c -o scripts/genksyms/parse.o scripts/genksyms/parse.c

source_scripts/genksyms/parse.o := scripts/genksyms/parse.c

deps_scripts/genksyms/parse.o := \
  /usr/include/assert.h \
  /usr/include/features.h \
  /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/include/stdlib.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stddef.h \
  /usr/include/sys/types.h \
  /usr/include/bits/types.h \
  /usr/include/bits/typesizes.h \
  /usr/include/time.h \
  /usr/include/endian.h \
  /usr/include/bits/endian.h \
  /usr/include/sys/select.h \
  /usr/include/bits/select.h \
  /usr/include/bits/sigset.h \
  /usr/include/bits/time.h \
  /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h \
  /usr/include/alloca.h \
  /usr/include/string.h \
  /usr/include/bits/string.h \
  /usr/include/bits/string2.h \
  scripts/genksyms/genksyms.h \
  /usr/include/stdio.h \
  /usr/include/libio.h \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/include/bits/wchar.h \
  /usr/include/gconv.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h \
  /usr/include/bits/stdio.h \

scripts/genksyms/parse.o: $(deps_scripts/genksyms/parse.o)

$(deps_scripts/genksyms/parse.o):
