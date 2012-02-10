#
#  This software includes code derived from xv6 which is
#  Copyright (c) 2006-2009 Frans Kaashoek, Robert Morris, Russ Cox,
#                        Massachusetts Institute of Technology
#
#  See LICENSE.MIT for the full licence details.
#

# Initial process execs /init.

#include <sys/syscall.h>
#include <sys/traps.h>


# exec(init, argv)
.globl start
start:
  pushl $argv
  pushl $init
  pushl $0  // where caller pc would be
  movl $SYS_exec, %eax
  int $T_SYSCALL

# for(;;) exit();
exit:
  movl $SYS_exit, %eax
  int $T_SYSCALL
  jmp exit

# char init[] = "/init\0";
init:
  .string "/init\0"

# char *argv[] = { init, 0 };
.p2align 2
argv:
  .long init
  .long 0

