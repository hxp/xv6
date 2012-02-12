include standard_defs.mk

xv6.img: boot/bootblock sys/kernel fs.img
	dd if=/dev/zero of=xv6.img count=10000
	dd if=boot/bootblock of=xv6.img conv=notrunc
	dd if=sys/kernel of=xv6.img seek=1 conv=notrunc

#xv6memfs.img: boot/bootblock kernelmemfs
#    dd if=/dev/zero of=xv6memfs.img count=10000
#    dd if=bootblock of=xv6memfs.img conv=notrunc
#    dd if=kernelmemfs of=xv6memfs.img seek=1 conv=notrunc

# kernelmemfs is a copy of kernel that maintains the disk image in memory
# instead of writing to a disk.  This is not so useful for testing persistent
# storage or exploring disk buffering implementations, but it is great for
# testing the kernel on real hardware without needing a scratch disk.
#MEMFSOBJS = $(filter-out ide.o,$(OBJS)) memide.o
#kernelmemfs: $(MEMFSOBJS) entry.o entryother initcode fs.img
#	$(LD) $(LDFLAGS) -Ttext 0x100000 -e main -o kernelmemfs entry.o  $(MEMFSOBJS) -b binary initcode entryother fs.img
#	$(OBJDUMP) -S kernelmemfs > kernelmemfs.asm
#	$(OBJDUMP) -t kernelmemfs | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernelmemfs.sym


fs.img: tools/mkfs README bin/_* 
	cp bin/_* .
	tools/mkfs fs.img README _* 
	rm _*

tools/mkfs: tools/mkfs.c
	gcc -o $(output) $(input)

### Emulators

bochs : fs.img xv6.img
	if [ ! -e .bochsrc ]; then ln -s dot-bochsrc .bochsrc; fi
	bochs -q

# try to generate a unique GDB port
GDBPORT = $(shell expr `id -u` % 5000 + 25000)

# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)

ifndef CPUS
CPUS := 2
endif

QEMUOPTS = -hdb fs.img xv6.img -smp $(CPUS) -m 512 $(QEMUEXTRA)

qemu: fs.img xv6.img
	$(QEMU) -serial mon:stdio $(QEMUOPTS)

qemu-memfs: xv6memfs.img
	$(QEMU) xv6memfs.img -smp $(CPUS)

qemu-nox: fs.img xv6.img
	$(QEMU) -nographic $(QEMUOPTS)

.gdbinit: .gdbinit.tmpl
	sed "s/localhost:1234/localhost:$(GDBPORT)/" < $^ > $@

qemu-gdb: fs.img xv6.img .gdbinit
	@echo "*** Now run 'gdb'." 1>&2
	$(QEMU) -serial mon:stdio $(QEMUOPTS) -S $(QEMUGDB)

qemu-nox-gdb: fs.img xv6.img .gdbinit
	@echo "*** Now run 'gdb'." 1>&2
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

.PHONY: clean
clean:
	mppc -r -v
