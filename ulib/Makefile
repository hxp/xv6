include standard_defs.mk

ulib.a: *.o
	$(TOOLPREFIX)ar cq $(output) $(inputs)
	$(TOOLPREFIX)ranlib $(output)

%.o: %.c
	$(CC) $(CFLAGS) -o $(output) $(input)

%.o: %.S
	$(CC) $(ASFLAGS) -o $(output) $(input)
