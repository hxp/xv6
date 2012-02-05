#include <sys/types.h>
#include <sys/stat.h>
#include <sys/user.h>

int
main(int argc, char *argv[])
{
  if(argc != 3){
    printf(2, "Usage: mv source dest\n");
    exit();
  }
  if(link(argv[1], argv[2]) < 0)
    printf(2, "can't move %s: failed\n", argv[1]);
  unlink(argv[1]);
  exit();
}
