// Daniel Christiansen
// ECE373
// HW #3
// User-space program to talk to pci driver

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define LED_ON  0x0006834E
#define LED_OFF 0x0006830F

int main() {
	int fd = -1, len, buf;

	// Open driver
	fd = open("/dev/ece_led", O_RDWR);
	if (fd < 1) {
		printf("\ncouldn't open driver.\n");
		return -1;
	}

	len = read(fd, &buf, sizeof(int));
	if (len < 0)
		printf("Couldn't read from driver: %d\n", len);
	else
		printf("Current blink rate: %d b/s\n", buf);

    sleep(5);

	printf("Writing -1 to driver\n");
	buf = -1;
	len = write(fd, &buf, sizeof(int));
	if (len < 0)
		printf("Couldn't write to driver: %d\n", len);
	
	len = read(fd, &buf, sizeof(int));
	if (len < 0)
		printf("Couldn't read from driver: %d\n", len);
	else
		printf("Current blink rate: %d b/s\n", buf);
	
	sleep(5);

    close(fd);

	return 0;
}
