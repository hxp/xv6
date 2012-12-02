//
//  This software includes code derived from xv6 which is
//  Copyright (c) 2006-2009 Frans Kaashoek, Robert Morris, Russ Cox,
//                        Massachusetts Institute of Technology
//
//  See LICENSE.MIT for the full licence details.
//

// Fake IDE disk; stores blocks in memory.
// Useful for running kernel without scratch disk.

#include <sys/types.h>
#include <sys/defs.h>
#include <sys/param.h>
#include <sys/mmu.h>
#include <sys/proc.h>
#include <sys/x86.h>
#include <sys/traps.h>
#include <sys/spinlock.h>
#include <sys/buf.h>

#ifdef MEMBLOCK

extern uchar _binary_fs_img_start[], _binary_fs_img_size[];

static uint32_t disksize;
static uint8_t *memdisk;

void
memdiskinit(void)
{
  memdisk = _binary_fs_img_start;
  disksize = (uint32_t)_binary_fs_img_size/512;
}

// Sync buf with disk. 
// If B_DIRTY is set, write buf to disk, clear B_DIRTY, set B_VALID.
// Else if B_VALID is not set, read buf from disk, set B_VALID.
void
memdiskrw(struct buf *b)
{
  uchar *p;

  if(!(b->flags & B_BUSY))
    panic("memblock: buf not busy");
  if((b->flags & (B_VALID|B_DIRTY)) == B_VALID)
    panic("memblock: nothing to do");
  if(b->dev != 255)
    panic("memblock: request not for disk 1");
  if(b->sector >= disksize)
    panic("block: sector out of range");

  p = memdisk + b->sector*512;
  
  if(b->flags & B_DIRTY){
    b->flags &= ~B_DIRTY;
    memmove(p, b->data, 512);
  } else
    memmove(b->data, p, 512);
  b->flags |= B_VALID;
}

#endif
