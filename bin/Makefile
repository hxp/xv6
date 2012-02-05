# /bin makefile

makepp_no_builtin_linker = 1

include standard_defs.mk


# ldflags to link binaries correctly
LDFLAGS = -N -e main -Ttext 0

default: _* _sh

ULIB = ../ulib.o ../usys.o ../printf.o ../umalloc.o

_%: %.o ../ulib.o ../usys.o ../printf.o ../umalloc.o
	$(LD) $(LDFLAGS) -o $(output) $(input) $(ULIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $(output) $(input)


