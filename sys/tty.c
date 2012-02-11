//
//  This software includes code derived from xv6 which is
//  Copyright (c) 2006-2009 Frans Kaashoek, Robert Morris, Russ Cox,
//                        Massachusetts Institute of Technology
//
//  See LICENSE.MIT for the full licence details.
//

//
//  Adapted by Joel Heikkila, Copyright (c) 2012
//

// tty input to/from uart, based off code from console.c

#include <sys/types.h>
#include <sys/defs.h>
#include <sys/param.h>
#include <sys/traps.h>
#include <sys/spinlock.h>
#include <sys/fs.h>
#include <sys/file.h>
#include <sys/memlayout.h>
#include <sys/mmu.h>
#include <sys/proc.h>
#include <sys/x86.h>

static int panicked = 0;

static struct {
  struct spinlock lock;
  int locking;
} tty;

void
ttyputc(int c)
{
  if(panicked){
    cli();
    for(;;)
      ;
  }

	uartputc(c);
}

#define TTY_INPUT_BUF 128
struct {
  struct spinlock lock;
  char buf[TTY_INPUT_BUF];
  uint r;  // Read index
  uint w;  // Write index
  uint e;  // Edit index
} tty_input;

#define C(x)  ((x)-'@')  // Control-x

void
ttyintr(int (*getc)(void))
{
	int c;

  acquire(&tty_input.lock);
  while((c = getc()) >= 0){
    if(c != 0 && tty_input.e-tty_input.r < TTY_INPUT_BUF) {
//      c = (c == '\r') ? '\n' : c;
      tty_input.buf[tty_input.e++ % TTY_INPUT_BUF] = c;
      uartputc(c);
//      if(c == '\n' || c == C('D') || tty_input.e == tty_input.r+TTY_INPUT_BUF){
        tty_input.w = tty_input.e;
        wakeup(&tty_input.r);
//      }
      break;
    }
  }
  release(&tty_input.lock);
}

int
ttyread(struct inode *ip, char *dst, int n)
{
  
//  cprintf("ttyread\n");	
  uint target;
  int c;

  iunlock(ip);
  target = n;
  acquire(&tty_input.lock);
  while(n > 0){
    while(tty_input.r == tty_input.w){
      if(proc->killed){
        release(&tty_input.lock);
        ilock(ip);
        return -1;
      }
      sleep(&tty_input.r, &tty_input.lock);
    }
    c = tty_input.buf[tty_input.r++ % TTY_INPUT_BUF];
    if(c == C('D')){  // EOF
      if(n < target){
        // Save ^D for next time, to make sure
        // caller gets a 0-byte result.
        tty_input.r--;
      }
      break;
    }
    *dst++ = c;
    --n;
//    if(c == '\n')
      break;
  }
  release(&tty_input.lock);
  ilock(ip);

  return target - n;
}

int
ttywrite(struct inode *ip, char *buf, int n)
{
	int i;

  iunlock(ip);
  acquire(&tty.lock);
  for(i = 0; i < n; i++)
    ttyputc(buf[i] & 0xff);
  release(&tty.lock);
  ilock(ip);

  return n;
}

void
ttyinit(void)
{
  initlock(&tty.lock, "tty");
  initlock(&tty_input.lock, "ttyinput");

  devsw[TTY].write = ttywrite;
  devsw[TTY].read = ttyread;
  tty.locking = 1;

//  picenable(IRQ_KBD);
//  ioapicenable(IRQ_KBD, 0);
}

