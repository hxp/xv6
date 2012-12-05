include standard_defs.mk

#xv6.img: boot/bootblock sys/kernel fs.img
#	dd if=/dev/zero of=xv6.img count=10000
#	dd if=boot/bootblock of=xv6.img conv=notrunc
#	dd if=sys/kernel of=xv6.img seek=1 conv=notrunc

xv6memfs.img: boot/bootblock sys/kernelmemfs fs.img
    dd if=/dev/zero of=xv6memfs.img count=10000
    dd if=boot/bootblock of=xv6memfs.img conv=notrunc
    dd if=sys/kernelmemfs of=xv6memfs.img seek=1 conv=notrunc

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
GDBPORT = 1234

# QEMU's gdb stub command line changed in 0.11
QEMUGDB =  -s

ifndef CPUS
CPUS := 2
endif

QEMUOPTS = -smp $(CPUS) -m 512 $(QEMUEXTRA) -serial mon:stdio


.PHONY: qemu
qemu: fs.img xv6.img
	$(QEMU) $(QEMUOPTS) -hdb fs.img xv6.img

qemu-memfs: xv6memfs.img
	$(QEMU) $(QEMUOPTS) xv6memfs.img -hdb ext2fs.img

qemu-nox: fs.img xv6.img
	$(QEMU) -nographic $(QEMUOPTS)

qemu-gdb: fs.img xv6.img 
	@echo "*** Now run 'gdb'." 1>&2
	$(QEMU) $(QEMUOPTS) -S $(QEMUGDB) -hdb fs.img xv6.img

qemu-gdb-memfs: xv6memfs.img
	$(QEMU) $(QEMUOPTS) -S $(QEMUGDB) xv6memfs.img -hdb ext2fs.img

qemu-nox-gdb: fs.img xv6.img .gdbinit
	@echo "*** Now run 'gdb'." 1>&2
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

.PHONY: clean
clean:
	mppc -r -v
