#include <sys/types.h>
#include <sys/user.h>

int main(int argc, char *argv[]) {
  if(argc != 4){
    printf(2, "Usage: mknod devicefile minor major\n");
    exit();
  }

 if(mknod(argv[1], atoi(argv[2]), atoi(argv[3])) < 0) {
   printf(2, "unable to create device file %s\n",argv[1]);
   exit();
 }
  exit();
}
