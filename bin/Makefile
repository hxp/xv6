# /bin makefile

makepp_no_builtin_linker = 1

include standard_defs.mk

CFLAGS += -Werror

# ldflags to link binaries correctly
LDFLAGS = -N -e main -Ttext 0

#ULIB = ../ulibc/printf.o ../ulibc/umalloc.o ../ulibc/usys.o ../ulibc/ulib.o 

default: _* _sh ../ulib/ulib.a

_%: %.o ../ulib/ulib.a
	$(LD) $(LDFLAGS) -o $(output) $(inputs)

%.o: %.c
	$(CC) $(CFLAGS) -o $(output) $(input)

%.o: %.S
	$(CC) $(ASFLAGS) -o $(output) $(input)
