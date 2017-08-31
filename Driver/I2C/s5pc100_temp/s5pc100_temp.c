#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

MODULE_LICENSE ("GPL");

#define LM75_REG_CONF		0x01
static const u8 LM75_REG_TEMP[3] = {
	0x00,		/* input */
	0x03,		/* max */
	0x02,		/* hyst */
};
struct lm75_data 
{
	u16 temp[3]; /* Register values,
						   0 = input
						   1 = max
						   2 = hyst */
};

static int lm75_major = 250;
static int lm75_minor = 0;
static int number_of_devices = 1;
static dev_t devno = 0;
static struct cdev cdev;
static struct i2c_client *new_client;
struct lm75_data *data;

static int lm75_read_value(struct i2c_client *client)
{
	struct i2c_msg msgs[2];
	int status;
	char buf1[2];
	char buf2[2];
	msgs[0].len = 1;
	msgs[0].addr = client->addr; // lm75 设备地址
	msgs[0].flags = 0;//write
	msgs[0].buf = buf1;
	msgs[0].buf[0] = LM75_REG_TEMP[0];
	msgs[1].len = 2;//读出的数据
	msgs[1].addr = client->addr;// lm75 设备地址 
	msgs[1].flags = I2C_M_RD;//read
	msgs[1].buf = buf2;//存放返回值的地址。

	status = i2c_transfer(client->adapter, msgs, 2);
	if(status < 0)
		return status;

//	printk("1 = %2x %2x\n", buf2[0], buf2[1]);
	return (buf2[0] << 8) | buf2[1];

}

static ssize_t lm75_read(struct file *file, char __user *buff, size_t count, loff_t *offset) 
{
	int status;

	status = lm75_read_value(new_client);
	if(status < 0)
	{
		return status;
	}

	printk("status = %x\n", status);
	if(copy_to_user(buff, (char *)&status, sizeof(status)))
		return -EFAULT;

	return 0;
}

static int lm75_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int lm75_release(struct inode *inode, struct file *file)
{
	return 0;
}

static struct file_operations lm75_fops = {
	.owner 	= THIS_MODULE,
	.read	= lm75_read,
	.open 	= lm75_open,
	.release	= lm75_release,
};


static int lm75_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret = 0;

	new_client = client;

	devno = MKDEV(lm75_major, lm75_minor);

	ret = register_chrdev_region(devno, number_of_devices, "lm75");
	if(ret)
	{
		printk("failed to register device number\n");
		goto err_register_chrdev_region;
	}

	cdev_init(&cdev, &lm75_fops);
	cdev.owner = THIS_MODULE;
	ret = cdev_add(&cdev, devno, number_of_devices);
	if(ret)
	{
		printk("failed to add device\n");
		goto err_cdev_add;
	}

	return 0;
err_cdev_add:
	unregister_chrdev_region(devno, number_of_devices);
err_register_chrdev_region:
	kfree(data);
	return ret;
}

static int lm75_remove(struct i2c_client *client)
{
	cdev_del(&cdev);
	unregister_chrdev_region(devno, number_of_devices);
	return 0;
}

enum lm75_type {		/* keep sorted in alphabetical order */
	lm75,
	lm75a,
};

static const struct i2c_device_id lm75_ids[] = {
	{ "lm75", lm75, },
	{ "lm75a", lm75a, },
	{ /* LIST END */ }
};

static struct i2c_driver lm75_driver = {
	.driver = {
		.name = "lm75",
	},
	.probe 		= lm75_probe,
	.remove 	= lm75_remove,
	.id_table	= lm75_ids,
};

static int __init s5pc100_lm75_init(void)
{
	return i2c_add_driver(&lm75_driver);
}

static void __exit s5pc100_lm75_exit(void)
{
	i2c_del_driver(&lm75_driver);
}

module_init(s5pc100_lm75_init);
module_exit(s5pc100_lm75_exit);
