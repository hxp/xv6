#include <sys/types.h>

#define		EXT2_ERROR_HANDLE_IGNORE	0x01
#define		EXT2_ERROR_HANDLE_REMOUNT	0x02
#define		EXT2_ERROR_HANDLE_PANIC		0x03

struct ext2_superblock {

	uint32_t	num_inodes;				// number of inodes in fs
	uint32_t	num_blocks;				// number of blocks in fs
	uint32_t	reserved_num;			// blocks reserved for superuser
	uint32_t	num_unaloc_blocks;		// number of blocks unallocated 
	uint32_t	num_unaloc_inodes;		// number of inodes unallocated
	uint32_t	first_data_block;		// first data block
	uint32_t	log_block_size;
	uint32_t	log_frag_size;
	uint32_t	blocks_in_group;		// number of blocks in block group
	uint32_t	frags_in_group;			// number of frags in each block group
	uint32_t	inodes_in_group;		// number of inodes in block group
	uint32_t	last_mount_time;		// unix time last mounted
	uint32_t	last_write_time;		// unix time last written to
	uint16_t	mount_num;				// times mounted since last fsck
	uint16_t	max_mount;				// number of times to mount before
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
	

} __attribute__((packed));


