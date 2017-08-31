#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/poll.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/system.h>

#include <mach/regs-gpio.h>
#include <mach/irqs.h>



MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("farsight");

static int irq_major = 250;
static int irq_minor = 0;
static struct cdev irq_cdev;
static int key;
struct fasync_struct *async_queue;  

static int irq_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int irq_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t irq_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{

	if(copy_to_user(buf, (char *)&key, count))
		return -ENOMEM;

	return count;
}

static int irq_fasync(int fd, struct file *filp, int mode)
{
	return fasync_helper(fd, filp, mode, &async_queue);
}

static struct file_operations s5pc100_irq_ops = {
	.owner = THIS_MODULE,
	.open = irq_open,
	.release = irq_release,
	.read = irq_read,
	.fasync = irq_fasync,
};

static int irq_setup_cdev(struct cdev *cdev, 
		struct file_operations *fops)
{
	int result;
	dev_t devno = MKDEV(irq_major, irq_minor);
	cdev_init(cdev, fops);
	cdev->owner = THIS_MODULE;
	result = cdev_add(cdev, devno, 1);
	if(result)
	{
		printk("irq: cdev add faiirq\n");
		return result;
	}
	return 0;
}

static irqreturn_t  irqhandler(int irqno, void *dev_id)
{
	printk("irq: interrupt %d\n", irqno);

	switch(irqno)
	{
		case IRQ_EINT(1):
			key = 1;
			break;
		case IRQ_EINT(2):
			key = 2;
			break;
		case IRQ_EINT(3):
			key = 3;
			break;
		case IRQ_EINT(4):
			key = 4;
			break;
		case IRQ_EINT(6):
			key = 5;
			break;
		case IRQ_EINT(7):
			key = 6;
			break;
	}
	if (async_queue)
       kill_fasync(&async_queue, SIGIO, POLL_IN);

	return IRQ_HANDLED;
}

static int __init s5pc100_irq_init(void)
{
	int result;
	dev_t devno = MKDEV(irq_major, irq_minor);
	result = register_chrdev_region(devno, 1, "s5pc100_irq");
	if(result)
	{
		printk("irq: unable to get major %d\n", irq_major);
		return result;
	}

	result = irq_setup_cdev(&irq_cdev, &s5pc100_irq_ops);
	if(result)
		goto err_add_cdev;

	writel((readl(S5PC100_GPH0_BASE) & ~(0xF << 4)) | (0x2 << 4), S5PC100_GPH0_BASE);
	writel((readl(S5PC100_GPH0_BASE) & ~(0xF << 8)) | (0x2 << 8), S5PC100_GPH0_BASE);
	writel((readl(S5PC100_GPH0_BASE) & ~(0xF << 12)) | (0x2 << 12), S5PC100_GPH0_BASE);
	writel((readl(S5PC100_GPH0_BASE) & ~(0xF << 16)) | (0x2 << 16), S5PC100_GPH0_BASE);
	writel((readl(S5PC100_GPH0_BASE) & ~(0xF << 24)) | (0x2 << 24), S5PC100_GPH0_BASE);
	writel((readl(S5PC100_GPH0_BASE) & ~(0xF << 28)) | (0x2 << 28), S5PC100_GPH0_BASE);

	result = request_irq(IRQ_EINT(1), irqhandler, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "EINT 1", NULL);	
	if(result)
		goto err1;
	result = request_irq(IRQ_EINT(2), irqhandler, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "EINT 2", NULL);	
	if(result)
		goto err2;
	result = request_irq(IRQ_EINT(3), irqhandler, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "EINT 3", NULL);	
	if(result)
		goto err3;
	result = request_irq(IRQ_EINT(4), irqhandler, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "EINT 4", NULL);	
	if(result)
		goto err4;
	result = request_irq(IRQ_EINT(6), irqhandler, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "EINT 6", NULL);	
	if(result)
		goto err5;
	result = request_irq(IRQ_EINT(7), irqhandler, IRQF_DISABLED|IRQF_TRIGGER_FALLING, "EINT 7", NULL);	
	if(result)
		goto err6;

	printk("irq: driver instalirq, with major %d!\n", irq_major);
	return 0;

err6:
	free_irq(IRQ_EINT(6), NULL);
err5:
	free_irq(IRQ_EINT(4), NULL);
err4:
	free_irq(IRQ_EINT(3), NULL);
err3:
	free_irq(IRQ_EINT(2), NULL);
err2:
	free_irq(IRQ_EINT(1), NULL);
err1:
	cdev_del(&irq_cdev);
err_add_cdev:
	unregister_chrdev_region(devno, 1);

	return result;
}

static void __exit s5pc100_irq_exit(void)
{
	dev_t devno = MKDEV(irq_major, irq_minor);
	cdev_del(&irq_cdev);
	unregister_chrdev_region(devno, 1);
	free_irq(IRQ_EINT(1), NULL);
	free_irq(IRQ_EINT(2), NULL);
	free_irq(IRQ_EINT(3), NULL);
	free_irq(IRQ_EINT(4), NULL);
	free_irq(IRQ_EINT(6), NULL);
	free_irq(IRQ_EINT(7), NULL);
	printk("irq: driver uninstalirq!\n");
}

module_init(s5pc100_irq_init);
module_exit(s5pc100_irq_exit);
