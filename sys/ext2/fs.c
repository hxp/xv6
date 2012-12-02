#include "ext2.h"
#include <sys/defs.h>
#include <sys/buf.h>

struct ext2_superblock *ext2sb;

void ext2_start() {

	int dev = 1;
	
	struct buf *b;

	b = bread(dev, 2);
	memmove (ext2sb, b->data, sizeof(*ext2sb));
	brelse(b);
	
	if (ext2sb->magic == 0xef53) {
		cprintf("Ext2 volume on device %x.\n", dev);

		cprintf("Volume has %d/%d blocks ", 
				ext2sb->num_blocks - ext2sb->num_unaloc_inodes, 
				ext2sb->num_blocks);
		cprintf("and %d/%d inodes.\n",
				ext2sb->num_inodes - ext2sb->num_unaloc_inodes,
				ext2sb->num_inodes);

	panic("ext2\n");
	}
}
