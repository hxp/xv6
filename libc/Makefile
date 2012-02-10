include standard_defs.mk

../libc.a: string/*.o
	$(TOOLPREFIX)ar cq $(output) $(inputs)
	$(TOOLPREFIX)ranlib $(output)

string/%.o: string/%.c
	$(CC) $(CFLAGS) -o $(output) $(input)

%.o: %.S
	$(CC) $(ASFLAGS) -o $(output) $(input)
