// User-space program to talk to driver

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define NEW_VAL 99

int main() {
	int fd, len, buf = 20;

	// Open char driver device
	fd = open("/dev/cdmodule", O_RDWR);
	if (fd == -1) {
		printf("\ncouldn't open driver.\n");
		return -1;
	}

	// Read syscall_val from device
	len = read(fd, &buf, sizeof(int));
	if (len < 1) {
		printf("\nCouldn't read from driver.\n");
		return -1;
	}

	printf("syscall_value is %d.\n", buf);
	
	// Attempt to write a new value
	printf("Attempting to write %d to the driver.\n", NEW_VAL);
	
	buf = NEW_VAL;
	len = write(fd, &buf, sizeof(int));
	if (len < 1) {
		printf("Couldn't write to driver.\n");
		printf("error no. %d.\n", len); 
		return -1;
	}

	// Check the attempt
	len = read(fd, &buf, sizeof(int));
	if (len < 1) {
		printf("Couldn't read from driver.\n");
		return -1;
	}

	printf("syscall_value is %d.\n", buf);

	return 0;
}
