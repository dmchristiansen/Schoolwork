// Daniel Christiansen
// ECE373
// HW #6

#include <stdio.h>
#include <pci/pci.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#define VENDOR_ID  0x8086
#define DEVICE_ID  0x1501
#define BAR_NO     0
#define LED_ON     0x0006834E
#define LED_OFF    0x0006830F

const unsigned int led_offset = 0x0E00;
const unsigned int gpr_offset = 0x04074;

struct pci_dev * find_dev(struct pci_access*);
void print_bars(struct pci_dev*);

void main() {
	int fd;
	void *ptr;
	uint32_t led_default, gpr;
	uint32_t *led_ptr, *gpr_ptr;	
	struct pci_access *pacc;
	struct pci_dev *pdev;

	// initialize pci_access struct
	// (this gives you a copy of the list of pci devices?)
	pacc = pci_alloc();
	pci_init(pacc);
	pci_scan_bus(pacc);

	// try to find correct pci_dev struct
	if (!(pdev = find_dev(pacc))) {
		printf("failed to access device.\n");
		goto dev_err;
	}

	// get BAR & mmap to userspace
	fd = open("/dev/mem", O_RDWR);
	if (fd < 1) {
		printf("/dev/mem couldn't be opened.\n");
		goto open_err;
	}
	printf("Attempting to mmap: %x, %x with fd %d\n", (uint)pdev->vendor_id, (uint)pdev->device_id, fd);
	ptr = mmap(NULL, (size_t)pdev->size[BAR_NO], PROT_READ|PROT_WRITE, 
		MAP_SHARED, fd, (size_t)pdev->base_addr[BAR_NO]);
	if ((size_t)ptr < 0) {
		printf("mmap failed\n");
		goto map_err;
	}
	printf("virtual addr: %p\n", ptr);
	led_ptr = (uint32_t*)(ptr + led_offset);
	gpr_ptr = (uint32_t*)(ptr + gpr_offset);
	printf("led addr:     %p\n", led_ptr);

	// save current LED reg value
	printf("LED reg: %x\n", (*led_ptr));
	led_default = *led_ptr;
	printf("Changing LED reg val.\n");

	// cycle through LED colors
	*led_ptr = 0x4040;
	sleep(2);

	*led_ptr = 0x0;
	sleep(2);

	int i;
	for (i = 0; i < 5; i = i + 1) {
		*led_ptr = 0x400000;
		sleep(1);
		*led_ptr = 0x000040;
		sleep(1);
		*led_ptr = 0x004000;
		sleep(1);
	}

	*led_ptr = led_default;

	// check good packets received
	printf("good packets received: %i\n", *gpr_ptr);

cleanup:
	munmap(ptr, (size_t)pdev->size[BAR_NO]);
map_err:
	close(fd);
open_err:
dev_err:
	pci_cleanup(pacc);

	return;
}

// function to loop through pci_dev list and return a pointer to the correct one
struct pci_dev * find_dev(struct pci_access * pacc) {
	struct pci_dev * pdev;

	for (pdev = pacc->devices; pdev; pdev = pdev->next) {
		if ((pdev->vendor_id == VENDOR_ID) && (pdev->device_id == DEVICE_ID))
			return pdev;
	}

	return pdev;
}

// prints the BARs and region sizes of a single device
void print_bars(struct pci_dev * pdev) {
	if (!pdev)
		return;	

	int i;
	for (i = 0; i < 6; i = i + 1) {
		printf("BAR: %08x, Region size: %08x\n", 
			(uint)pdev->base_addr[i], (uint)pdev->size[i]);
	}
}
