
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
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/system.h>

#include <mach/regs-gpio.h>
#include <mach/irqs.h>


MODULE_LICENSE ("GPL");

static int adc_major = 250;
static int adc_minor = 0;
static int number_of_cdev = 1;

static struct cdev cdev;
static dev_t devno;
static int flag = 0;
static struct clk *myclk;
void * ADCCON,// adc control register 0xf3000000
	 * ADCDAT0,//conversion datas values 0xf300000c
	 * ADCCLRINT,//INT_ADC Interrupt clear 0xf3000018
	 * ADCMUX;// analog input channel select 0xf300001c
wait_queue_head_t my_queue;


static void create_map(void)
{
	ADCCON = ioremap (0xf3000000,4);
	ADCDAT0 = ioremap (0xf300000c,4);
	writel((readl(ADCDAT0) & 0x0000),ADCDAT0);
	ADCCLRINT = ioremap (0xf3000018,4);
	ADCMUX = ioremap (0xf300001c,4);
	writel(readl(ADCMUX) & 0x0,ADCMUX);
	writel((readl(ADCCON)& (~0xffff))|1<<14|20<<6,ADCCON);
}
static void delete_map(void)
{
	iounmap (ADCCON);
	iounmap (ADCDAT0);
	iounmap (ADCCLRINT);
	iounmap (ADCMUX);
}

static int adc_open(struct inode*inode, struct file *file)
{
	create_map();
	init_waitqueue_head(&my_queue);
	printk (KERN_INFO "Hy.......adc_open success!!\n");
	return 0;
}
static int adc_release(struct inode *inode,struct file *file)
{
	delete_map();
	printk (KERN_INFO "Hmmmmm.......adc_release success!!\n");
	return 0;
}
static ssize_t adc_read(struct file *file,char __user *buf,size_t count,loff_t *offp)
{
	int result;

    flag = 0;
	writel(readl(ADCCON) | 0x1,ADCCON);
	wait_event_interruptible(my_queue,flag == 0);//睡眠
		result = readl(ADCDAT0) & 0x3ff;
		result = 3300*result/1024;
	   if(copy_to_user(buf,(char *)&result,count))
		   return -ENOMEM;
	

	return count;
}

/***打开时钟*****/
static void open_adc_clock(void)
{
	if((myclk = clk_get(NULL,"adc")) == NULL)
			printk (KERN_WARNING "fail to clk_get");
	clk_enable(myclk);
}
static void close_adc_clock(void)
{
	clk_disable(myclk);
	clk_put(myclk);
}

static struct file_operations adc_fops = {
	.owner = THIS_MODULE,
	.open  = adc_open,
	.release = adc_release,
	.read = adc_read,
};

static int adc_setup_cdev(void)
{
	int errno;
	cdev_init(&cdev,&adc_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops  = &adc_fops;
	errno = cdev_add (&cdev,devno,number_of_cdev);

	return errno;
}
static irqreturn_t adc_irqhandler(int irqno,void *dev_id)
{
	flag = 1;
	wake_up_interruptible(&my_queue);//唤醒等待队列
	writel(readl(ADCCLRINT) | 0x1,ADCCLRINT);
	return IRQ_HANDLED;
}

static int __init adc_2_init(void)
{
	int result,irq_result;
	devno = MKDEV(adc_major,adc_minor);
	result = register_chrdev_region(devno,number_of_cdev,"adc");
	if(result){
		printk(KERN_WARNING  "fail to register_chrdev_region result = %d\n",result);
		return result;
	}
	if(adc_setup_cdev())
		goto error_add_cdev;
	open_adc_clock();
	irq_result = request_irq(IRQ_ADC,adc_irqhandler,IRQF_DISABLED,"ADC",NULL);
	if(irq_result)
		goto error;

	printk(KERN_INFO "moudle insmod adc success!!!\n");
	return 0;
error:
    printk (KERN_WARNING "fail to request_irq irqno \n");
	unregister_chrdev_region(devno,number_of_cdev);
	return irq_result;
error_add_cdev:
	unregister_chrdev_region(devno,number_of_cdev);
	printk(KERN_WARNING "fail to cdev_add and fail to insmod adc \n");
	return adc_setup_cdev();
}

static void __exit adc_2_exit(void)
{
	close_adc_clock();
	free_irq(IRQ_ADC,NULL);
	cdev_del(&cdev);
	unregister_chrdev_region(devno,number_of_cdev);

	printk(KERN_INFO "module rmmod adc success !!!\n");
}

module_init (adc_2_init);
module_exit (adc_2_exit);



