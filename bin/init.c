// init: The initial user-level program

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ulib/ulib.h>
#include <sys/fcntl.h>

char *argv[] = { "sh", 0 };

int
main(void)
{

	ktest();
	int pid, wpid;

	if(open("console", O_RDWR) < 0) 
		mknod("console", 1, 1);

  if(open("tty", O_RDWR) < 0){
    mknod("tty", 2, 1);
    open("tty", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
