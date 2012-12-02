#Cross-compiling (e.g., on Mac OS X)
TOOLPREFIX = i586-elf-

# Path to this directory

BASEPATH = /Users/joel/src/xv6

# Path to QEMU
QEMU = /Users/joel/bin/qemu/bin/qemu-system-i386

CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)as
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
AR = $(TOOLPREFIX)ar
RANLIB = $(TOOLPREFIX)ranlib

# optimize 
#CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer

# non-optimized 
CFLAGS += -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -ggdb -m32 -fno-omit-frame-pointer
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector) -c

# includes

CFLAGS += -I$(BASEPATH)/include

ASFLAGS = -m32 -gdwarf-2 -Wa,-divide -c -x assembler-with-cpp

ASFLAGS += -I$(BASEPATH)/include

