#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ulib/ulib.h>

int
main(int argc, char **argv)
{
  int i;

  if(argc < 1){
    printf(2, "usage: kill pid...\n");
    exit();
  }
  for(i=1; i<argc; i++)
    kill(atoi(argv[i]));
  exit();
}
