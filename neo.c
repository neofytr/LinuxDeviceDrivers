#include <linux/module.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("neofyt (rajisbornforcoc@gmail.com)");
MODULE_DESCRIPTION("Basic read loadable kernel module");

static struct proc_dir_entry *custom_proc_node;
static struct proc_ops neo_proc_ops;

static int neo_module_init(void)
{
    // NULL in the 3rd argument creates the new file in the root of the proc directory
    custom_proc_node = proc_create("neo", S_IRUSR | S_IRGRP | S_IROTH, NULL, &neo_proc_ops);
    return 0;
}

static void neo_module_exit(void)
{
    proc_remove(custom_proc_node);
}

module_init(neo_module_init);
module_exit(neo_module_exit);
