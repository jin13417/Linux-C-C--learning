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

#include "s5pc100_pwm.h"

MODULE_LICENSE ("GPL");

static int pwm_major = 250;
static int pwm_minor = 0;
static int number_of_cdev = 1;

static struct cdev cdev;
static dev_t devno;
void * GPDCON;
void * CLK_GATE_D1_3;//gate for PWM clock 0xe010052c
void * TCFGO;//presclaer values 0xea000000
void * TCFG1;//divider values   0xea000004
void * CON;  //timer control register 0xea000008
void * TCNTB1; //TIMER1 count buffer register 0xea000018
void * TCMPB1; //timer1 compare register 0xea00001c


static ssize_t pwm_open (struct inode *inode,struct file *file)
{
   GPDCON = ioremap(0xe0300080,4);
   writel((readl(GPDCON) & (~0xf0)) | 0x20,GPDCON);
//   CLK_GATE_D1_3 = ioremap(0xe010052c,4);
 // writel(readl(CLK_GATE_D1_3) | 1 << 6,CLK_GATE_D1_3);
   TCFGO = ioremap(0xea000000,4);
   TCFG1 = ioremap(0xea000004,4);
   writel((readl(TCFG1)& (~0xf0)) + (3 << 4),TCFG1);
   CON = ioremap(0xea000008,4);
   TCNTB1 = ioremap(0xea000018,4);
 //  writel((readl(TCNTB1) & 0x0000000) + 3000 ,TCNTB1);
  // TCMPB1 = ioremap(0xea00001c,4);
//   writel((readl(TCMPB1) & 0x0000000) + 1500 ,TCMPB1);


	return 0;
}
static ssize_t pwm_release (struct inode *inode,struct file *file)
{
	return 0;
}
static int pwm_ioctl (struct inode *inode,struct file *file,unsigned int cmd,unsigned long arg)
{
	switch (cmd)	{
	case SET_PRE:

		printk(KERN_WARNING "SET_PRE \n");
		writel((readl(TCFGO) & (~0xff)) + arg,TCFGO);   
		break;
	case SET_CNT:
		printk(KERN_WARNING "SET_CNT \n");
   writel((readl(TCNTB1) & 0x0000000) + arg ,TCNTB1);

	    writel(readl(CON)& ~(0xf <<8) | 0x2 << 8 , CON);//set timer1 Manual Update
		writel(readl(CON)& ~(0xf <<8) | 0x9 << 8 , CON);//clean Manual Update bin and start up TIMER1
		break;
	default:
		break;
	}


	return 0;
}
/**********结构体初始化*****************/
static struct file_operations pwm_fops = {
	.owner = THIS_MODULE,
	.open  = pwm_open,
    .release = pwm_release,
	.ioctl = pwm_ioctl,
};
/******字符设备结构体初始化及注册******/
static int pwm_setup_cdev(void)
{
	int errno;
	cdev_init(&cdev,&pwm_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops  = &pwm_fops;
	errno = cdev_add(&cdev,devno,number_of_cdev);
	return errno;
}

/*******module ismod function*******/
static int __init pwm_3_init(void)
{
	int result;
	/***构建设备号及注册设备号******/
	devno = MKDEV(pwm_major,pwm_minor);
	result = register_chrdev_region(devno,number_of_cdev,"pwm");
	if(result){
		printk(KERN_WARNING "fail to register_chrdev_region result = %d \n",result);
		return result;
	}
	if(pwm_setup_cdev()){//判断字符设备是否注册成功
		printk(KERN_WARNING "fail to cdev_add \n");
		unregister_chrdev_region(devno,number_of_cdev);
		return 0;
	}


	printk(KERN_INFO "module ismod pwm success !!!\n");
	return 0;
}
/*****module rmmod function ******/
static void __exit pwm_3_exit (void)
{
	cdev_del(&cdev);
	unregister_chrdev_region(devno,number_of_cdev);

	printk(KERN_INFO "module rmmod pwm success !!!\n");
}

module_init (pwm_3_init);
module_exit (pwm_3_exit);


