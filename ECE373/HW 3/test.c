// Daniel Christiansen
// ECE373
// HW #3
// User-space program to talk to pci driver

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define LED_ON  0xE
#define LED_OFF 0xF 

int main() {
	int fd, len, buf;

	// Open driver
	fd = open("/dev/pci_driver", O_RDWR);
	if (fd == -1) {
		printf("\ncouldn't open driver.\n");
		return -1;
	}

	// Read LED register value from device
	len = read(fd, &buf, sizeof(int));
	if (len < 1) {
		printf("\nCouldn't read from driver.\n");
		return -1;
	}

	printf("LED register contents is: 0x%x.\n", buf);
	
	// Attempt to turn the LED on
	printf("Attempting to write 0x%x to the driver.\n", LED_ON);
	
	buf = LED_ON;
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

	printf("LED register contents is: 0x%x.\n", buf);
    
    sleep(2);

	// Attempt to turn the LED off
	printf("Attempting to write 0x%x to the driver.\n", LED_OFF);
	
	buf = LED_OFF;
	len = write(fd, &buf, sizeof(int));
	if (len < 1) {
		printf("Couldn't write to driver.\n");
		printf("error no. %d.\n", len); 
		return -1;
	}

    close(fd);

	return 0;
}
