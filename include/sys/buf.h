//
//  This software includes code derived from xv6 which is
//  Copyright (c) 2006-2009 Frans Kaashoek, Robert Morris, Russ Cox,
//                        Massachusetts Institute of Technology
//
//  See LICENSE.MIT for the full licence details.
//

struct buf {
  int flags;
  uint8_t dev;
  uint64_t sector;
  struct buf *prev; // LRU cache list
  struct buf *next;
  struct buf *qnext; // disk queue
  uint8_t data[512];
};
#define B_BUSY  0x1  // buffer is locked by some process
#define B_VALID 0x2  // buffer has been read from disk
#define B_DIRTY 0x4  // buffer needs to be written to disk

