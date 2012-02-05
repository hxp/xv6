# /bin makefile

makepp_no_builtin_linker = 1

include standard_defs.mk


# ldflags to link binaries correctly
LDFLAGS = -N -e main -Ttext 0

#ULIB = ../ulibc/printf.o ../ulibc/umalloc.o ../ulibc/usys.o ../ulibc/ulib.o 

default: _* _sh ../libc.a

_%: %.o $(ULIB)
	$(LD) $(LDFLAGS) -o $(output) $(input) -L.. -lc

%.o: %.c
	$(CC) $(CFLAGS) -o $(output) $(input)


