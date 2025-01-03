#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("neofyt");
MODULE_DESCRIPTION("My first dynamically loadable kernel module neo");

static int neo_module_init(void)
{
    printk("Hello, World! (from neo)\n");
    return 0;
}

static void neo_module_exit(void)
{
    printk("Goodbye! (from neo)\n");
}

module_init(neo_module_init);
module_exit(neo_module_exit);
