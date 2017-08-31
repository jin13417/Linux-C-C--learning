
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

static int register_request_irq(void);
MODULE_LICENSE("GPL");

static int key_major = 250;
static int key_minor = 0;
static int number_of_devices = 1;
static  struct cdev cdev;
static  int key_number;
struct fasync_struct *async_queue;//异步通知指针
static dev_t dev = 0;

void * WU_INTO_7_CON,*GPH0CON,*GPH0DAT;

static ssize_t key_open(struct inode *inode,struct file*file)
{
	WU_INTO_7_CON = ioremap(0xe0300e00,4);
//	GPH0CON = ioremap(0xe0300c00,4);
	writel((readl(WU_INTO_7_CON) & (~0xff0ffff0)) | 0x22022220,WU_INTO_7_CON);//设置为下降沿模式
//	writel((readl(GPH0CON)&(~0xff0ffff0)) | 0x22022220,GPH0CON);//设置为中断模式

	if(!register_request_irq())//判断中断是否申请成功
		printk("irqno register error !!!!\n");

	printk("Hi......key_test program opened!!!\n");
	return 0;
}
static ssize_t key_release(struct inode *inode,struct file*file)
{
	printk("Hmmmmm........key_test program closed~~~~\n");
	return 0;
}
//读函数
static int key_read (struct file *file,char __user *buf,size_t count,loff_t*ppos)
{
	if(copy_to_user(buf,(char *)&key_number,count))
		return	-EFAULT;
			
	return count;
}
//异步通知函数:
static int key_fasync(int fd,struct file *file,int mode)
{
	return fasync_helper(fd,file,mode,&async_queue);
}
//中断处理函数
static irqreturn_t handler(int irqno,void *dev_id)
{
	switch (irqno)
	{
	case IRQ_EINT(1):	key_number = 1; break;
	case IRQ_EINT(2):	key_number = 2; break;
	case IRQ_EINT(3):	key_number = 3; break;
	case IRQ_EINT(4):	key_number = 4; break;
	case IRQ_EINT(6):	key_number = 5; break;
	case IRQ_EINT(7):	key_number = 6; break;
	}
	if(async_queue)//产生异步读信号
		kill_fasync(&async_queue,SIGIO,POLL_IN);


	return IRQ_HANDLED;
}
//申请中断号
static int register_request_irq(void)
{
	int ret;
	if((ret = request_irq(IRQ_EINT(1),handler,IRQF_DISABLED| IRQF_TRIGGER_FALLING,"key1",NULL)) != 0)
		goto error1;
	if((ret = request_irq(IRQ_EINT(2),handler,IRQF_DISABLED| IRQF_TRIGGER_FALLING,"key2",NULL)) != 0)
		goto error2;
	if((ret = request_irq(IRQ_EINT(3),handler,IRQF_DISABLED|IRQF_TRIGGER_FALLING,"key3",NULL)) != 0)
		goto error3;
	if((ret = request_irq(IRQ_EINT(4),handler,IRQF_DISABLED|IRQF_TRIGGER_FALLING,"key4",NULL)) != 0)
		goto error4;
	if((ret = request_irq(IRQ_EINT(6),handler,IRQF_DISABLED|IRQF_TRIGGER_FALLING,"key5",NULL)) != 0)
		goto error5;
	if((ret = request_irq(IRQ_EINT(7),handler,IRQF_DISABLED|IRQF_TRIGGER_FALLING,"key6",NULL)) != 0)
		goto error6;
	return ret;
error6:
	free_irq(IRQ_EINT(6),NULL);
error5:
	free_irq(IRQ_EINT(4),NULL);
error4:
	free_irq(IRQ_EINT(3),NULL);
error3:
	free_irq(IRQ_EINT(2),NULL);
error2:
	free_irq(IRQ_EINT(1),NULL);
error1:
	cdev_del(&cdev);
	unregister_chrdev_region(dev,number_of_devices);
	return ret;


}
struct file_operations key_fops = {
	.owner = THIS_MODULE,
	.open  = key_open,
	.release = key_release,
	.read = key_read,
	.fasync =key_fasync, 
};
//初始化及注册字符设备
static void key_setup_cdev(void)
{
	int error;
	cdev_init (&cdev,&key_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops   = &key_fops;
	error = cdev_add(&cdev,dev,number_of_devices);
	if(error)
		printk(KERN_NOTICE "ERROR %d adding key_setup_cdev\n",error);
}

//模块加载函数
static int __init key_2_init (void)
{
	int result;
	dev = MKDEV(key_major,key_minor);
	if((result = register_chrdev_region(dev,number_of_devices,"key")) < 0 )
	{
		printk(KERN_WARNING "key :can't get major number %d\n",key_major);
		return result;
	}


	key_setup_cdev();//申请中断


	printk (KERN_INFO "char device register sucess!!!!!\n");
	return 0;
}

static void __exit key_2_exit (void)
{
	//释放中断号
   
	free_irq(IRQ_EINT(7),NULL);
	free_irq(IRQ_EINT(6),NULL);
	free_irq(IRQ_EINT(4),NULL);
	free_irq(IRQ_EINT(3),NULL);
	free_irq(IRQ_EINT(2),NULL);
	free_irq(IRQ_EINT(1),NULL);
//取消映射
   iounmap(WU_INTO_7_CON);
   iounmap(GPH0CON);
   iounmap(GPH0DAT);

	cdev_del(&cdev);//删除字符设备
	unregister_chrdev_region(dev,number_of_devices);//

	printk (KERN_INFO "char device clear up sucess!!!!!\n");
}

module_init (key_2_init);
module_exit (key_2_exit);
	


