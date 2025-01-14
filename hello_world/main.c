#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/stat.h>
#include <asm/current.h>
#include <linux/errno.h>

static char *whom = "world";
static int howmany = 1;

module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

MODULE_LICENSE("GPL");

static int hello_init(void)
{
    printk(KERN_INFO "The process is \"%s\" (pid %d)\n", current->comm, current->pid);
    return 0;
}

static void hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);