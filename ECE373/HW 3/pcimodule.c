// Daniel Christiansen
// ECE 373
// HW #3 - PCI Driver
// 05/01/17

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/pci.h>
#include <asm/io.h>

#define DEV_NAME   "pci_driver"
#define DEV_COUNT  1	
#define VENDOR_ID  0x8086
#define DEVICE_ID  0x150C
#define LED_MASK   0xFFFFFFF0
#define LED_OFFSET 0x00E00

// Function prototypes
static int pci_open(struct inode *inode, struct file *file);
static ssize_t pci_read(struct file *file, char __user *buf, size_t len, loff_t *offset);
static ssize_t pci_write(struct file *file, const char __user *buf, size_t len, loff_t *offset);

static struct dev_struct {
	struct cdev cdev;
	dev_t cd_node;
	void * __iomem hw_addr;
} char_dev;


// overview:
// enable memory
// find location of bar
// give me virtual address to access bar
static int pci_probe(struct pci_dev *pdev, const struct pci_device_id *pdid)
{
	int err, bars;
	resource_size_t mmio_start, mmio_len;
	
	printk(KERN_INFO "Entering pci_probe() function.\n");

	// declare dev_struct?

	err = pci_enable_device(pdev);
	if(err) {
		printk(KERN_INFO "pci_enable_device() failed.\n");
		return err;
	}
	printk(KERN_INFO "pci_device_enable() sucessful.\n");
		
	// get mask for BARs matching IORESOURCE_MEM
	bars = pci_select_bars(pdev, IORESOURCE_MEM);
	printk(KERN_INFO "pci_select_bars() sucessful.\n");
    
	// claim I/O regions pointed to by BARs indicated by mask
	err = pci_request_selected_regions(pdev, bars, DEV_NAME);
	if(err) {
		printk(KERN_INFO "pci_request_selected_regions failed w/ %d\n", err);
		return err;
	}
	printk(KERN_INFO "pci_request_selected_regions successful.\n");

	// grab control of bus
	pci_set_master(pdev);
	printk(KERN_INFO "pci_set_master sucessful.\n");

	// get start/len of BAR
	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);

	// get virtual address of BAR
	char_dev.hw_addr = ioremap(mmio_start, mmio_len);
	if(!char_dev.hw_addr)
		printk(KERN_INFO "ioremap failed.\n");

	printk(KERN_INFO "hw_addr = %p\n", char_dev.hw_addr);

	printk(KERN_INFO "pci_probe() complete.\n");

	return 0;
}

static void pci_remove(struct pci_dev *pdev)
{
    int bars;

	printk(KERN_INFO "Entering pci remove function.\n");

	iounmap(char_dev.hw_addr);
	bars = pci_select_bars(pdev, IORESOURCE_MEM);
	pci_release_selected_regions(pdev, bars);
}



// Device structure

static DEFINE_PCI_DEVICE_TABLE(pci_test_table) = {
    { PCI_DEVICE(VENDOR_ID, DEVICE_ID) },
    { },
};

static struct pci_driver test_pci_driver = {
    .name = DEV_NAME,
    .id_table = pci_test_table,
    .probe = pci_probe,
    .remove = pci_remove,
};



// Operations structure
static struct file_operations pci_fops = {
	.owner = THIS_MODULE,
	.open  = pci_open,
	.read  = pci_read,
	.write = pci_write,
};

static int mp;
module_param(mp, int, S_IRUSR | S_IWUSR);

static int pci_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "pci driver in the pci_open() function.\n");

	return 0;
}

static ssize_t pci_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
	u32 led_val;

	printk(KERN_INFO "pci_read() function executing.\n");

	// Check for null pointer
	if (!buf)
		return -EINVAL;

	led_val = readl(char_dev.hw_addr + LED_OFFSET);

	// returns amount of memory still to be copied
	// (should be 0)
	if(copy_to_user(buf, &led_val, sizeof(u32))) {
		return -EFAULT;
	}
	*offset += len;

	printk(KERN_INFO "data read from device.\n");
	return sizeof(int);
}

// Copy data from user space to the device.
// Returns -1 on error, otherwise returns the number of bytes written.
static ssize_t pci_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    char *kbuf;
    int ret, led_val;

	printk(KERN_INFO "pci_write() function executing.\n");

	// Check for offset greater than the size of the data...
	//if (*offset >= sizeof(int))
	//	return 0;

	// Check for null pointer
	if (!buf)
		return -EINVAL;

    kbuf = kmalloc(len, GFP_KERNEL);

    if (!kbuf) {
        ret = -ENOMEM;
        goto out;
    }

	// returns amount of memory still to be written
	// (should be 0)
	if (copy_from_user(kbuf, buf, sizeof(int))) {
        ret = -EFAULT;
        goto mem_out;
    }

	ret = len;
    
    //read - mask - write led_val
    printk(KERN_INFO "Starting RMW.\n");
    led_val = readl(char_dev.hw_addr + LED_OFFSET);
    printk(KERN_INFO "(Read) LED val = 0x%x\n", led_val);
    led_val = led_val & LED_MASK; 
    printk(KERN_INFO "(AND)LED val = 0x%x\n", led_val);
    led_val = led_val | *((u32*)(kbuf));
    printk(KERN_INFO "(OR)LED val = 0x%x\n", led_val);
	writel(led_val, char_dev.hw_addr + LED_OFFSET);


mem_out:
    kfree(kbuf);
out:
    return ret;
}

int __init pci_init(void)
{
	// Allocate device number
	if (alloc_chrdev_region(&char_dev.cd_node, 0, DEV_COUNT, DEV_NAME)) {
		printk(KERN_INFO "error allocating device node for %s.\n", DEV_NAME);
		return -1;
	}

	printk(KERN_INFO "device node allocated for %s.\n", DEV_NAME);
	printk(KERN_INFO "%s allocated at %d, %d.\n", DEV_NAME,
		MAJOR(char_dev.cd_node), MINOR(char_dev.cd_node));

	// Initialize character device
	cdev_init(&char_dev.cdev, &pci_fops);
	char_dev.cdev.owner = THIS_MODULE;

	// Add device to the kernel
	if (cdev_add(&char_dev.cdev, char_dev.cd_node, DEV_COUNT)) {
		printk(KERN_ERR "cdev_add() failed for %s.\n", DEV_NAME);
		unregister_chrdev_region(char_dev.cd_node, DEV_COUNT);
		return -1;
	}

    return pci_register_driver(&test_pci_driver);
}

void __exit pci_exit(void)
{
	cdev_del(&char_dev.cdev);
	unregister_chrdev_region(char_dev.cd_node, DEV_COUNT);
	pci_unregister_driver(&test_pci_driver);	

	printk(KERN_INFO "pci driver module unloaded.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Christiansen");

module_init(pci_init);
module_exit(pci_exit);
