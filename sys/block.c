#include <sys/types.h>
#include <sys/buf.h>
#include <sys/defs.h>

#define		BLOCK_DEV_IDE0		0
#define		BLOCK_DEV_IDE1		1
#define		BLOCK_DEV_MEM		0xff

void blockrw(struct buf *b) {

	cprintf("DEBUG: read block dev %x, sector %x\n", b->dev, b->sector);

	switch ( b -> dev ) {

		case BLOCK_DEV_IDE0: 
		case BLOCK_DEV_IDE1:
			iderw(b);
			break;

#ifdef MEMBLOCK
		case BLOCK_DEV_MEM:
			memdiskrw(b);
			break;
#endif
		default:
			panic("block: unknown device");
	}
}

