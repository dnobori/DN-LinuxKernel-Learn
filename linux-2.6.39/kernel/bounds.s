	.file	"bounds.c"
# GNU C version 4.1.2 20080704 (Red Hat 4.1.2-55) (i386-redhat-linux)
#	compiled by GNU C version 4.1.2 20080704 (Red Hat 4.1.2-55).
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# 渡されたオプション:  -nostdinc
# -I/root/kernel/linux-2.6.39/arch/x86/include -Iinclude -D__KERNEL__
# -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DKBUILD_STR(s)=#s
# -DKBUILD_BASENAME=KBUILD_STR(bounds) -DKBUILD_MODNAME=KBUILD_STR(bounds)
# -isystem -include -MD -m32 -msoft-float -mregparm=3
# -mpreferred-stack-boundary=2 -march=i686 -maccumulate-outgoing-args
# -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -auxbase-strip -g -O2 -Wall
# -Wundef -Wstrict-prototypes -Wno-trigraphs
# -Werror-implicit-function-declaration -Wno-format-security
# -Wno-sign-compare -Wdeclaration-after-statement -Wno-pointer-sign -p
# -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks
# -freg-struct-return -ffreestanding -fstack-protector
# -fno-asynchronous-unwind-tables -fno-omit-frame-pointer
# -fno-optimize-sibling-calls -fno-inline-functions-called-once
# -fverbose-asm
# 有効オプション:  -falign-loops -fargument-alias -fbranch-count-reg
# -fcaller-saves -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fcse-skip-blocks -fdefer-pop -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations -ffunction-cse
# -fgcse -fgcse-lm -fguess-branch-probability -fident -fif-conversion
# -fif-conversion2 -fipa-pure-const -fipa-reference -fivopts
# -fkeep-static-consts -fleading-underscore -floop-optimize
# -floop-optimize2 -fmath-errno -fmerge-constants -foptimize-register-move
# -fpeephole -fpeephole2 -fprofile -freg-struct-return -fregmove
# -freorder-blocks -freorder-functions -frerun-cse-after-loop
# -frerun-loop-opt -fsched-interblock -fsched-spec
# -fsched-stalled-insns-dep -fschedule-insns2 -fshow-column
# -fsplit-ivs-in-unroller -fstack-protector -fstrength-reduce
# -fthread-jumps -ftrapping-math -ftree-ccp -ftree-ch -ftree-copy-prop
# -ftree-copyrename -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-fre
# -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize -ftree-lrs
# -ftree-pre -ftree-salias -ftree-sink -ftree-sra -ftree-store-ccp
# -ftree-store-copy-prop -ftree-ter -ftree-vect-loop-version -ftree-vrp
# -funit-at-a-time -fvar-tracking -fverbose-asm -fzero-initialized-in-bss
# -m32 -m96bit-long-double -maccumulate-outgoing-args -malign-stringops
# -mfused-madd -mieee-fp -mno-fancy-math-387 -mno-red-zone -mpush-args
# -mtls-direct-seg-refs

	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
# Compiler executable checksum: 391ea76ef17128f7cf6721bdef1a3431

	.p2align 4,,15
.globl foo
	.type	foo, @function
foo:
.LFB2:
	.file 1 "kernel/bounds.c"
	.loc 1 15 0
	pushl	%ebp	#
.LCFI0:
	movl	%esp, %ebp	#,
.LCFI1:
	call	mcount
	.loc 1 15 0
	.loc 1 17 0
#APP
	
->NR_PAGEFLAGS $23 __NR_PAGEFLAGS	#
	.loc 1 18 0
	
->MAX_NR_ZONES $4 __MAX_NR_ZONES	#
	.loc 1 19 0
	
->NR_PCG_FLAGS $7 __NR_PCG_FLAGS	#
	.loc 1 21 0
#NO_APP
	popl	%ebp	#
	ret
.LFE2:
	.size	foo, .-foo
	.section	.debug_frame,"",@progbits
.Lframe0:
	.long	.LECIE0-.LSCIE0
.LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE0:
.LSFDE0:
	.long	.LEFDE0-.LASFDE0
.LASFDE0:
	.long	.Lframe0
	.long	.LFB2
	.long	.LFE2-.LFB2
	.byte	0x4
	.long	.LCFI0-.LFB2
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE0:
	.text
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB2-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI1-.Ltext0
	.long	.LFE2-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	0x0
	.long	0x0
	.section	.debug_info
	.long	0x92
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.Ldebug_line0
	.long	.Letext0
	.long	.Ltext0
	.long	.LASF11
	.byte	0x1
	.long	.LASF12
	.long	.LASF13
	.uleb128 0x2
	.long	.LASF0
	.byte	0x1
	.byte	0x6
	.uleb128 0x2
	.long	.LASF1
	.byte	0x1
	.byte	0x8
	.uleb128 0x2
	.long	.LASF2
	.byte	0x2
	.byte	0x5
	.uleb128 0x2
	.long	.LASF3
	.byte	0x2
	.byte	0x7
	.uleb128 0x3
	.string	"int"
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.long	.LASF4
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.long	.LASF5
	.byte	0x8
	.byte	0x5
	.uleb128 0x2
	.long	.LASF6
	.byte	0x8
	.byte	0x7
	.uleb128 0x2
	.long	.LASF7
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.long	.LASF4
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.long	.LASF8
	.byte	0x1
	.byte	0x6
	.uleb128 0x2
	.long	.LASF9
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.long	.LASF10
	.byte	0x1
	.byte	0x2
	.uleb128 0x4
	.byte	0x1
	.string	"foo"
	.byte	0x1
	.byte	0xf
	.byte	0x1
	.long	.LFB2
	.long	.LFE2
	.long	.LLST0
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x16
	.value	0x2
	.long	.Ldebug_info0
	.long	0x96
	.long	0x80
	.string	"foo"
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.value	0x0
	.value	0x0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0x0
	.long	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF6:
	.string	"long long unsigned int"
.LASF5:
	.string	"long long int"
.LASF0:
	.string	"signed char"
.LASF9:
	.string	"long int"
.LASF12:
	.string	"kernel/bounds.c"
.LASF4:
	.string	"unsigned int"
.LASF7:
	.string	"long unsigned int"
.LASF3:
	.string	"short unsigned int"
.LASF11:
	.string	"GNU C 4.1.2 20080704 (Red Hat 4.1.2-55)"
.LASF10:
	.string	"_Bool"
.LASF13:
	.string	"/root/kernel/linux-2.6.39"
.LASF2:
	.string	"short int"
.LASF8:
	.string	"char"
.LASF1:
	.string	"unsigned char"
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-55)"
	.section	.note.GNU-stack,"",@progbits
