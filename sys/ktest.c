// ktest.c

// this is basically a simple framework for testing kernel functions
// that need to be called from userland.  In normal compilation it
// should basically be a NOP

extern void ext2_start();

void sys_ktest () {

	ext2_start();

	panic("ktest: kernel testing routine called\n");
}
