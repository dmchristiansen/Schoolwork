// Daniel Christiansen
// ECE 373
// HW #4 - Timers
// 05/03/17

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/pci.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/timer.h>

#define DEV_NAME   "ece_led"
#define DEV_COUNT  1	
#define VENDOR_ID  0x8086
#define DEVICE_ID  0x150C
#define LED_OFFSET 0x00E00
#define LED_ON     0x0006834E
#define LED_OFF    0x0006830F


// Function prototypes
static int pci_open(struct inode *inode, struct file *file);
static int pci_release(struct inode *inode, struct file *file);
static ssize_t pci_read(struct file *file, char __user *buf, size_t len, loff_t *offset);
static ssize_t pci_write(struct file *file, const char __user *buf, size_t len, loff_t *offset);

static struct dev_struct {
	struct cdev cdev;
	dev_t cd_node;
	void * __iomem hw_addr;
	struct class * class_ptr;
	struct device * device_ptr;
	int bps;
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

static struct timer_list timer;

// Operations structure

static struct file_operations pci_fops = {
	.owner = THIS_MODULE,
	.open  = pci_open,
	.release = pci_release,
	.read  = pci_read,
	.write = pci_write,
};

static int blink_rate = 2;
module_param(blink_rate, int, S_IRUSR | S_IWUSR);

// toggles led & starts new timer
static void blink(unsigned long zero)
{
	int reg_val;
	if (char_dev.bps > 0) {
		reg_val = readl(char_dev.hw_addr + LED_OFFSET);
		reg_val = (reg_val == LED_ON) ? LED_OFF : LED_ON;
		writel(reg_val, char_dev.hw_addr + LED_OFFSET);
		mod_timer(&timer, jiffies + ((HZ / char_dev.bps) / 2)); 
	} else {
		writel(LED_OFF, char_dev.hw_addr + LED_OFFSET);
		mod_timer(&timer, jiffies + HZ);
	}
}

// sets up & starts timer
static int pci_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "open\n");

	char_dev.bps = blink_rate;
	setup_timer(&timer, blink, 0);
	if (char_dev.bps)
		mod_timer(&timer, jiffies + ((HZ / char_dev.bps) / 2)); 
	else
		mod_timer(&timer, jiffies + HZ);

	return 0;
}

// turns off led & stops timer
static int pci_release(struct inode *inode, struct file *file)
{   
	printk(KERN_INFO "release\n");

	writel(LED_OFF, char_dev.hw_addr + LED_OFFSET);
	del_timer_sync(&timer);

    return 0;
}

static ssize_t pci_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
	printk(KERN_INFO "pci_read() function executing.\n");

	// Check for null pointer
	if (!buf)
		return -EINVAL;

	// returns amount of memory still to be copied
	// (should be 0)
	if(copy_to_user(buf, &char_dev.bps, sizeof(int))) {
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
	int ret;

	printk(KERN_INFO "pci_write() function executing.\n");

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

	// check for negative values
	if (*(int*)kbuf < 0) {
		ret = -EINVAL;
		goto mem_out;
	}

	ret = len;
	char_dev.bps = *((int*)kbuf);

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
	if (cdev_add(&char_dev.cdev, char_dev.cd_node, DEV_COUNT))
		goto add_fail;

	char_dev.class_ptr = class_create(THIS_MODULE, DEV_NAME);
	if (!char_dev.class_ptr)
		goto class_fail;

	char_dev.device_ptr = device_create(char_dev.class_ptr, NULL, 
		char_dev.cd_node, NULL, DEV_NAME);
	if(!char_dev.device_ptr)
		goto device_fail;

	char_dev.bps = blink_rate;

	printk(KERN_INFO "ece_led module loaded sucessfully.\n");

	return pci_register_driver(&test_pci_driver);

device_fail:
	class_destroy(char_dev.class_ptr);
class_fail:
	cdev_del(&char_dev.cdev);
add_fail:
	unregister_chrdev_region(char_dev.cd_node, DEV_COUNT);
	return -1;
}

void __exit pci_exit(void)
{
	pci_unregister_driver(&test_pci_driver);	
	device_destroy(char_dev.class_ptr, char_dev.cd_node);
	class_destroy(char_dev.class_ptr);
	cdev_del(&char_dev.cdev);
	unregister_chrdev_region(char_dev.cd_node, DEV_COUNT);

	printk(KERN_INFO "pci driver module unloaded.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Christiansen");

module_init(pci_init);
module_exit(pci_exit);
