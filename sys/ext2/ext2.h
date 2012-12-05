#include <sys/types.h>

#define		EXT2_ERROR_HANDLE_IGNORE	0x01
#define		EXT2_ERROR_HANDLE_REMOUNT	0x02
#define		EXT2_ERROR_HANDLE_PANIC		0x03

struct ext2_superblock {

	uint32_t	num_inodes;				// number of inodes in fs
	uint32_t	num_blks;				// number of blocks in fs
	uint32_t	reserved_num;			// blocks reserved for superuser
	uint32_t	num_unaloc_blks;		// number of blocks unallocated 
	uint32_t	num_unaloc_inodes;		// number of inodes unallocated
	uint32_t	first_data_blk;			// first data block
	uint32_t	log_blk_sz;
	uint32_t	log_frag_sz;
	uint32_t	blks_in_grp;			// number of blocks in block group
	uint32_t	frags_in_grp;			// number of frags in each block group
	uint32_t	inodes_in_grp;			// number of inodes in block group
	uint32_t	last_mount_time;		// unix time last mounted
	uint32_t	last_write_time;		// unix time last written to
	uint16_t	mnt_num;				// times mounted since last fsck
	uint16_t	max_mnt;				// number of times to mount before
										// fsck mandatory
	uint16_t	magic;					// magic number 0xef53
	uint16_t	fs_state;				// file system state
										//		1 = clean
										//		2 = errors
	uint16_t	error_handle;			// what to do if errors above
										//		1 = ignore
										//		2 = remount r/o
										//		3 = no recovery
	uint16_t	minor_rev;				// minor revision level
	uint32_t	last_fsck_time;			// unix time last fsck
	uint32_t	max_nofsck_time;		// unix time between fscks
	uint32_t	os_id;					
	uint32_t	major_rev;
	uint16_t	uid_reserved;			// uid that can use reserved blocks
	uint16_t	gid_reserved;

	/* extended superblock attributes follow */

	uint32_t	first_nonresv_inode;	// fixed at 11 in < 1.0
	uint16_t	inode_struct_size;		// fixed at 128 in < 1.0
	uint16_t	backup_blkgrp;			// which blkgrp backup sb is part of
	uint32_t	opt_features;
	uint32_t	req_features;
	uint32_t	ro_features;
	uint8_t		uuid[16];
	uint8_t		vol_name[16];
	uint8_t		last_mnt_path[64];
	uint32_t	compression_used;
	uint8_t		num_blk_prealoc_file;
	uint8_t		num_blk_prealoc_dir;
	uint16_t	unused;

	/* journalling stuff */

//	uint8_t		journal_uuid[16];
//	uint32_t	journal_inode;
//	uint32_t	journal_dev;
//	uint32_t	last_orphan;
	

} __attribute__((packed));

struct ext2_descriptor_table_entry {
	uint32_t	blk_bm;					// first block of block bitmap 
	uint32_t	inode_bm;
	uint32_t	inode_table;
	uint16_t	free_blks;
	uint16_t	free_inodes;
	uint16_t	used_dirs;
	uint8_t		unused[14];				// descript. tbl. entries are 32 byte

} __attribute__((packed));


// inode table entry is 128 bytes
struct ext2_itable_entry {
	uint16_t	mode;
	uint16_t	uid;
	uint32_t	sz;
	uint32_t	atime;
	uint32_t	ctime;
	uint32_t	mtime;
	uint32_t	dtime;
	uint16_t	gid;
	uint16_t	links;
	uint32_t	blks;
	uint32_t	flags;
	uint32_t	unused0;
	uint32_t	blk_ptr[15];
	uint32_t	gen;					// generation
	uint32_t	file_acl;
	uint32_t	dir_acl;
	uint32_t	unused1;				// should be 0
	uint8_t		unused2[12];
} __attribute__((packed));


