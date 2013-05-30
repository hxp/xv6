#include "ext2.h"
#include <sys/defs.h>
#include <sys/buf.h>
#include <sys/types.h>

#define EXT2_BLOCKSIZE	1024

struct buf *b;
uint8_t blkbuf[1024]; // 4096 bytes is the largest block we support

struct ext2_superblock *ext2sb;
struct ext2_descriptor_table_entry ext2dt[32];
struct ext2_itable_entry ext2itable[8];

struct ext2_dir_entry ext2de;

int dev = 1;

void ext2_readblk(int dev, uint32_t block) {

	b = bread(dev, block * 2);
	memmove (blkbuf, b->data, 512);
	brelse(b);

	b = bread(dev, block * 2 + 1);
	memmove (blkbuf + 512, b-> data, 512);
	brelse(b);
}

uint32_t ext2_calc_inode_bg (uint32_t inode) {

	return (inode -1) / ext2sb->inodes_in_grp;
}

uint32_t ext2_calc_inode_local_idx(uint32_t inode) {

	return (inode - 1) % ext2sb->inodes_in_grp;
}

uint32_t ext2_read_dir_entry(uint32_t offset) {

	if (offset > EXT2_BLOCKSIZE - 8) {
		return -1;
	}
	int *p = &blkbuf + offset;
	int len;

	len = (uint16_t)*(p + 4);

	ext2de.file_type = (uint8_t)*p;
	
	int i = ext2de.name_len ;
	for (i; i < ext2de.name_len; i++)
		ext2de.name[i] = *(p + i);

	return ext2de.rec_len;
}

void ext2_start() {


	ext2_readblk(1, 1);
	memmove (ext2sb, blkbuf, sizeof(*ext2sb));

	// sanity checks
	//
	// magic number valid?
	if (ext2sb->magic != 0xef53)
		panic("ext2: magic number incorrect");

	// Linux doesn't support frag != blk sz and neither do we
	if (ext2sb->log_blk_sz != ext2sb->log_frag_sz)
		panic("ext2: block size != frag size, this is unsupported.");

	// currently only support a blocksize of 1 KiB
	if (1024 << ext2sb->log_blk_sz != 1024)
		panic("ext2: block size is not 1 KiB, presently unsupported.");

	cprintf("Ext2 volume on device %x, version %d.%d\n", dev, 
			ext2sb->major_rev, ext2sb->minor_rev);

	cprintf("Block size is %d B\n", 1024 << ext2sb->log_blk_sz);

	cprintf("Volume has %d/%d blocks ", 
			ext2sb->num_blks - ext2sb->num_unaloc_blks, 
			ext2sb->num_blks);
	cprintf("and %d/%d inodes.\n",
			ext2sb->num_inodes - ext2sb->num_unaloc_inodes,
			ext2sb->num_inodes);

	ext2_readblk(1, 2);				// read first blk descript table
	
	memmove(ext2dt, blkbuf, EXT2_BLOCKSIZE);

	cprintf("inode table at blk: %d\n", ext2dt[0].inode_table);

	ext2_readblk(1, ext2dt[0].inode_table);
	memmove(ext2itable, blkbuf, EXT2_BLOCKSIZE);

	cprintf("root dir created: %d\n", ext2itable[1].ctime);
	cprintf("root dir 1st block at %d\n", ext2itable[1].blk_ptr[0]);

	ext2_readblk(1, ext2itable[1].blk_ptr[0]);

	ext2_read_dir_entry(0);
}
