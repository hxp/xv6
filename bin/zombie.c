// Create a zombie process that 
// must be reparented at exit.

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/user.h>

int
main(void)
{
  if(fork() > 0)
    sleep(5);  // Let child exit before parent.
  exit();
}
