# /bin makefile

makepp_no_builtin_linker = 1

TOOLPREFIX = i586-elf-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld

CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector) -c
LDFLAGS = -N -e main -Ttext 0
ULIB = ../ulib.o ../usys.o ../printf.o ../umalloc.o

default: _* 

_%: %.o ../ulib.o ../usys.o ../printf.o ../umalloc.o
	$(LD) $(LDFLAGS) -o $(output) $(input) $(ULIB)

%.o  %.d: %.c
	$(CC) $(CFLAGS) -o $(output) $(input)
