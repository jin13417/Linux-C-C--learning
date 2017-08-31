#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<asm/io.h>

#include"led.h"

#define GPG3CON  0xE03001C0
#define GPG3DAT  0xE03001C4


MODULE_LICENSE("GPL");

int led_major = 250;
int led_minor = 0;
int number_of_devices = 1;


struct cdev cdev;
dev_t dev = 0;
void *conp = NULL, *datp = NULL;





static int led_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "HEY! device opened\n");
	return 0;
}

static int led_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "HEY! device closed\n");
	return 0;
}


int led_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	switch(cmd)
	{
	case LED_ON: 
		writel(readl(datp) | (1 << arg) ,datp);
		break;
	case LED_OFF:
		writel(readl(datp) & ~(1 << arg) ,datp);
		break;
	default:
		break;

	}
}




//ssize_t led_write (struct file *filp, const char __user *, size_t, loff_t *);

struct file_operations led_fops = {
	.owner = THIS_MODULE,
		.open = led_open,
		.release = led_release,
		.ioctl = led_ioctl,
		//.write = led_write,
};


struct class *my_class;


static void char_reg_setup_cdev(void)
{
	int error, devno = MKDEV(led_major, led_minor);
	cdev_init(&cdev, &led_fops);
	cdev.owner = THIS_MODULE;
	error = cdev_add(&cdev, devno, 1);
	if(error)
		printk(KERN_NOTICE "Error %d adding char_reg_setup_cdev", error);
	
	my_class = class_create(THIS_MODULE, "led_class");
	if(IS_ERR(my_class))
	{
		printk("Err: failed in creating class.\n");
		return;
	}

	device_create(my_class, NULL, devno, NULL, "led");
}



static int __init led_2_init(void)
{
	int result;
	u32 con;
	dev = MKDEV(led_major, led_minor);
	if(led_major)
	{
		result = register_chrdev_region(dev, number_of_devices, "led");
	}
	else
	{
		result = alloc_chrdev_region(&dev, led_minor, number_of_devices, "led");
		led_major = MAJOR(dev);

	}
	if(result < 0)
	{
		printk(KERN_WARNING "led: can't get major number %d\n", led_major);
		return result;
	}

	char_reg_setup_cdev();
	printk(KERN_INFO "Registered character driver\n");

	conp = ioremap(GPG3CON, 4);
	datp = ioremap(GPG3DAT, 4);

	con = readl(conp);
	con = (con & (~(0xffff))) | 0x1111;
	writel(con, conp);
	
	return 0;

}

static void __exit led_2_exit(void)
{
	dev_t devno = MKDEV(led_major, led_minor);
	cdev_del(&cdev);
	unregister_chrdev_region(devno, number_of_devices);
	printk(KERN_INFO "char driver cleaned up\n");

	device_destroy(my_class, devno);
	class_destroy(my_class);

	iounmap(conp);
	iounmap(datp);
}


module_init(led_2_init);
module_exit(led_2_exit);
