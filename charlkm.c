#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#define DEVICE_NAME "charlkm"
#define CLASS_NAME "charlkm_cls"

#define LOG_TITLE "[CHARLKM] "
#define MSG_SIZE 256

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zonda Yang");
MODULE_DESCRIPTION("Simple character device driver for LKM");
MODULE_VERSION("0.1");

static int majorNumber;
static char message[MSG_SIZE] = {0};
static short messageSize;
static int OpenNumbers = 0;
static struct class* charlkmClass = NULL;
static struct device* charlkmDevice = NULL;

// module functions
static int __init charlkm_init(void);
static void __exit charlkm_exit(void);

// file operation functions
static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);

// define file operation
static struct file_operations fops = {
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release,
};

static int __init charlkm_init(void)
{
    printk(KERN_INFO LOG_TITLE "Initializing the charlkm\n");

    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0) {
        printk(KERN_ALERT LOG_TITLE "Register a major number fail\n");
        return majorNumber;
    }
    printk(KERN_INFO LOG_TITLE "Current major number: %d\n", majorNumber);

    charlkmClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(charlkmClass)) {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT LOG_TITLE "Register device class fail\n");
        return PTR_ERR(charlkmClass);
    }
    printk(KERN_INFO LOG_TITLE "Device class registered\n");

    charlkmDevice = device_create(charlkmClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(charlkmDevice)) {
        class_destroy(charlkmClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT LOG_TITLE "Register device fail\n");
        return PTR_ERR(charlkmDevice);
    }
    printk(KERN_INFO LOG_TITLE "Device registered\n");
    return 0;
}

static void __exit charlkm_exit(void)
{
    device_destroy(charlkmClass, MKDEV(majorNumber, 0));
    class_unregister(charlkmClass);
    class_destroy(charlkmClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO LOG_TITLE "Byebye\n");
}

static int device_open(struct inode* inodep, struct file* fliep)
{
    OpenNumbers++;
    printk(KERN_INFO LOG_TITLE "Device has been opened %d times\n", OpenNumbers);
    return 0;
}

static int device_release(struct inode* inodep, struct file* fliep)
{
    printk(KERN_INFO LOG_TITLE "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file* fliep, char* buffer, size_t len, loff_t* offset)
{
    int error_count = 0;
    error_count = copy_to_user(buffer, message, messageSize);

    if (error_count == 0) {
        printk(KERN_INFO LOG_TITLE "Sent %d characters to the user\n", messageSize);
        messageSize = 0;
        return 0;
    } else {
        printk(KERN_INFO LOG_TITLE "Failed to send %d characters to the user\n", error_count);
        return -EFAULT;
    }
}

static ssize_t device_write(struct file* fliep, const char* buffer, size_t len, loff_t* offset)
{
    char *buf_internal;

    buf_internal = kmalloc(len, GFP_KERNEL);
    if (buf_internal == NULL) {
        return -ENOMEM;
    }

    if (copy_from_user(buf_internal, buffer, len)) {
        kfree(buf_internal);
        return -EFAULT;
    }

    snprintf(message, MSG_SIZE, "%s(%zu letters)", buf_internal, len);
    messageSize = strlen(message);
    printk(KERN_INFO LOG_TITLE "Received %zu characters from the user\n", len);
    kfree(buf_internal);
    return len;
}

module_init(charlkm_init);
module_exit(charlkm_exit);