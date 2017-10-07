#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GAPL");

int paramTest;
module_param(paramTest,int,S_IRUSR|S_IWUSR);

static int param_init(void)
{
	printk(KERN_ALERT "Showing the parameter demo");
	printk(KERN_ALERT"Value of paramTest is: %d",paramTest);
	return 0;
}
static int param_exit(void)
{
	printk(KERN_ALERT "Exiting");
}
module_init(param_init);
module_exit(param_exit);
