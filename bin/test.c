#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ulib/ulib.h>
#include <sys/fcntl.h>

char buf[40];

int main(int argc, char *argv[]) {
	
	int fd = open("file", O_CREATE | O_RDWR);

	lseek(fd, 500, SEEK_CUR);
	printf(fd,"stuff\n\n");

	exit();
}
