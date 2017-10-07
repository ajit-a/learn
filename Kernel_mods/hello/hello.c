#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello..Ajit here");
	return 0;
}
static int hello_exit(void)
{
	printk(KERN_ALERT "Exiting");
}
module_init(hello_init);
module_exit(hello_exit);
