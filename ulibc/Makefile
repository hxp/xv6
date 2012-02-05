include standard_defs.mk

../ulibc.a: *.o
	$(TOOLPREFIX)ar cq ../libc.a $(inputs)
	$(TOOLPREFIX)ranlib ../libc.a

%.o: %.c
	$(CC) $(CFLAGS) -o $(output) $(input)

%.o: %.S
	$(CC) $(ASFLAGS) -o $(output) $(input)
