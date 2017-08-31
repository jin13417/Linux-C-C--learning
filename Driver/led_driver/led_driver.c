#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>
#include<asm/io.h>

#include <asm/system.h>
#include <mach/regs-gpio.h>
//#include <linux/lsab.h>
#include <linux/sched.h>
#include "led.h"

MODULE_LICENSE ("GPL");
int led_major = 250;
int led_minor = 0;
int number_of_devices = 1;

struct cdev cdev;//cdev 结构体定义

dev_t devno ;


void * GPG3CON;//0xe03001c0
void * GPG3DAT;//0xe03001c4
static void led_on (unsigned long arg)
{
	writel(readl(GPG3DAT) | (1 << arg),GPG3DAT);
	//writel(readl(S5PC100_GPG3_BASE+4) | (1 << arg),S5PC100_GPG3_BASE + 4);
}
static void led_off(unsigned long arg)
{
	writel(readl(GPG3DAT)& ~(1 << arg),GPG3DAT);
	//writel(readl(S5PC100_GPG3_BASE + 4) & ~(1 << arg),S5PC100_GPG3_BASE + 4);
}

static ssize_t led_open (struct inode * inode,struct file *file)
{
	GPG3CON = ioremap(0xe03001c0,4);
	GPG3DAT = ioremap(0xe03001c4,4);
	writel((readl(GPG3CON) & ~0xFFFF) | 0x1111,GPG3CON);
	writel(readl(GPG3DAT) & ~0xf,GPG3DAT);
//	writel(readl(GPG3DAT) | 0xf,GPG3DAT);


/*	writel((readl(S5PC100_GPG3_BASE) & ~0xFFFF) | 0x1111,S5PC100_GPG3_BASE);//设置GPG3CON相应的位
	writel(readl(S5PC100_GPG3_BASE+4) & ~0xF,S5PC100_GPG3_BASE);//初始化GPG3DAT为低电平

	writel(readl(S5PC100_GPG3_BASE+4) | (1 << 0),S5PC100_GPG3_BASE + 4);
	writel(readl(S5PC100_GPG3_BASE+4) | (1 << 1),S5PC100_GPG3_BASE + 4);*/
	printk(KERN_INFO "Hi.......led_open success!!\n");
	return 0;
}
static ssize_t led_release(struct inode *inode,struct file *file)
{
	printk(KERN_INFO "Hmmmm......led_release success !!\n");
	return 0;
}
static int led_ioctl(struct inode *inode,struct file * file,unsigned int cmd,unsigned long arg)
{
	printk(KERN_INFO "Hmmmm..........\n");
	switch (cmd)
	{
	case LED_ON:     led_on(arg);    break;
	case LED_OFF:    led_off(arg);   break;
	default:                         break;
	}
	return 0;
}


static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.open  = led_open,
	.ioctl  =  led_ioctl,
	.release = led_release,
};

static int led_setup_cdev(void)
{
	int error;
	cdev_init(&cdev,&led_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops  = &led_fops;
	error = cdev_add(&cdev,devno,number_of_devices);
	return error;
}
		

//module insmod function
static int __init led_2_init(void)
{
	int result;

	devno = MKDEV(led_major,led_minor);//构建设备号
	//申请设备号，失败打印错误信息
	result = register_chrdev_region (devno,number_of_devices,"led");
	if(result < 0)
		printk(KERN_WARNING "fail to register_chrdev_region !!!!\n");

	if(led_setup_cdev())//初始化注册字符设备
	goto error_add_cdev;

	//insmod sucess
	printk(KERN_INFO "insmod led module success!!!\n");
	return 0;
error_add_cdev://注册失败释放设备号，打印错误信息
	unregister_chrdev_region(devno,number_of_devices);
	printk(KERN_WARNING "fail to cdev_add and insmod led module!!! \n");
	return 0;

}
//module insmod function
static void __exit led_2_exit(void)
{
	cdev_del(&cdev);//卸载字符设备
	unregister_chrdev_region(devno,number_of_devices);

	printk(KERN_INFO "rmmod led module success!!\n");

}
module_init (led_2_init);
module_exit (led_2_exit);

