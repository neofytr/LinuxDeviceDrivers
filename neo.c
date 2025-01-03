#include <linux/module.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("neofyt (rajisbornforcoc@gmail.com)");
MODULE_DESCRIPTION("Basic read loadable kernel module");

static struct proc_dir_entry *custom_proc_node;
static struct proc_ops neo_proc_ops;

static ssize_t neo_read(struct file *file_ptr, char __user *user_space_buffer, size_t count, loff_t *offset);

static ssize_t neo_read(struct file *file_ptr, char __user *user_space_buffer, size_t count, loff_t *offset)
{
    printk("neo_read\n");
    return 0;
}

static int neo_module_init(void)
{
    neo_proc_ops.proc_read = neo_read; // binding neo_read function to read on /proc/neo

    // NULL in the 3rd argument creates the new file in the root of the proc directory
    custom_proc_node = proc_create("neo", S_IRUSR | S_IRGRP | S_IROTH, NULL, &neo_proc_ops);
    if (!custom_proc_node)
    {
        return -1;
    }
    return 0;
}

static void neo_module_exit(void)
{
    proc_remove(custom_proc_node);
}

module_init(neo_module_init);
module_exit(neo_module_exit);
