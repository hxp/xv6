#include <sys/types.h>
#include <unistd.h>
#include <ulib/ulib.h>
#include <sys/fcntl.h>
#include <math.h>

int main(int argc, char *argv[]) {

	int cons = open("/console", O_RDWR);

	printf(1, "%d\n", cons);

	double x;
	for (x = 0; x < 7; x += 0.005) {
		printf(cons, "%d: %d\n", (int) (x * 100000000), (int) tan(x) * 100000000);
	}
	exit();
}
