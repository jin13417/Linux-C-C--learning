#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
MODULE_LICENSE("Dual BSD/GPL");

static int lm75_major = 250;
static int lm75_
enum lm75_type{
	lm75,lm75a,
};
static struct i2c_driver_id lm75_ids[] = {
	{"lm75",lm75},
	{"lm75a",lm75},
};
static int lm75_probe(struct i2c_client * i2c_client,const struct i2c_device_id * i2c_device_id )
{


}
static int lm75_remove(struct i2c_client * i2c_client)
{
	return 0;
}
static struct i2c_driver lm75_driver = {
	.driver = {
		.name = "lm75",
	},
	.probe = lm75_probe,
	.remove = lm75_remove,
	.id_table = lm75_ids,
};

static int __init i2c_2_init(void)
{
	if(i2c_add_driver(&lm75_driver))
		printk(KERN_WARNING "fail to i2c_add_driver \n");
	printk("indmod lm75_driver success!!\n");
	return 0;
}

static void __exit i2c_2_exit(void)
{
	i2c_del_driver(&lm75_driver);
	printk("rmmod lm75_driver success!\n");
}

module_init(i2c_2_init);
module_exit(i2c_2_exit);
