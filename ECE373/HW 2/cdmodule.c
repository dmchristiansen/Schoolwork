// Daniel Christiansen
// ECE 373
// HW #2 - Character Driver
// 04/19/17

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEV_NAME "char_driver"
#define DEV_COUNT 1	

// Function prototypes
static int cd_open(struct inode *inode, struct file *file);
static ssize_t cd_read(struct file *file, char __user *buf, size_t len, loff_t *offset);
static ssize_t cd_write(struct file *file, const char __user *buf, size_t len, loff_t *offset);

// Device structure
static struct dev_struct {
	struct cdev cdev;
	dev_t cd_node;
	int syscall_val;
} char_dev;

// Operations structure
static struct file_operations cd_fops = {
	.owner = THIS_MODULE,
	.open  = cd_open,
	.read  = cd_read,
	.write = cd_write,
};

static int mp;
module_param(mp, int, S_IRUSR | S_IWUSR);

static int cd_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "character driver in the cd_open() function.\n");

	return 0;
}

// Copy data from the device to user space.
// Returns -1 on error, otherwise returns the number of bytes read.
static ssize_t cd_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
	printk(KERN_INFO "cd_read() function executing.\n");

	// Check for offset greater than size of the data...
	//if (*offset >= sizeof(int))
	//	return 0;

	// Check for null pointer
	if (!buf)
		return -EINVAL;

	// returns amount of memory still to be copied
	// (should be 0)
	if(copy_to_user(buf, &char_dev.syscall_val, sizeof(int))) {
		return -EFAULT;
	}
	*offset += len;

	printk(KERN_INFO "data read from device.\n");
	return sizeof(int);
}

// Copy data from user space to the device.
// Returns -1 on error, otherwise returns the number of bytes written.
static ssize_t cd_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    char *kbuf;
    int ret;

	printk(KERN_INFO "cd_write() function executing.\n");

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

    // Interpret the buffer as an integer
    char_dev.syscall_val = *((int*)kbuf);

    printk(KERN_INFO "Userspace wrote \"%d\" to us.\n", char_dev.syscall_val);

mem_out:
    kfree(kbuf);
out:
    return ret;
}

int __init cd_init(void)
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
	cdev_init(&char_dev.cdev, &cd_fops);
	char_dev.cdev.owner = THIS_MODULE;
	char_dev.syscall_val = mp;

	// Add device to the kernel
	if (cdev_add(&char_dev.cdev, char_dev.cd_node, DEV_COUNT)) {
		printk(KERN_ERR "cdev_add() failed for %s.\n", DEV_NAME);
		unregister_chrdev_region(char_dev.cd_node, DEV_COUNT);
		return -1;
	}

	return 0;
}

void __exit cd_exit(void)
{
	cdev_del(&char_dev.cdev);
	unregister_chrdev_region(char_dev.cd_node, DEV_COUNT);
	printk(KERN_INFO "character driver module unloaded.\n");
}

MODULE_LICENSE("GPL");

module_init(cd_init);
module_exit(cd_exit);
