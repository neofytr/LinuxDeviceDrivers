#include <linux/module.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("neofyt (rajisbornforcoc@gmail.com)");
MODULE_DESCRIPTION("Basic read loadable kernel module");

static struct proc_ops jiffies_proc_ops;
static struct proc_dir_entry *jiff_dir_entry;

ssize_t jiffies_read(struct file *proc_file, char *__user user_buffer, size_t count_to_read, loff_t *offset_into_file);

ssize_t jiffies_read(struct file *proc_file, char *__user user_buffer, size_t count_to_read, loff_t *offset_into_file)
{
    char jiffies_buf[256];
    ssize_t rv;

    if (*offset_into_file)
    {
        return 0;
    }

    rv = snprintf(jiffies_buf, 256, "jiffies: %lu\n", jiffies);
    if (copy_to_user(user_buffer, jiffies_buf, rv))
    {
        return -EFAULT;
    }

    *offset_into_file += rv;

    return rv;
}

static int jiffies_module_init(void)
{
    jiffies_proc_ops.proc_read = jiffies_read;
    jiff_dir_entry = proc_create("jiffies", S_IRUGO, NULL, &jiffies_proc_ops);
    if (!jiff_dir_entry)
    {
        return -1;
    }
    return 0;
}

static void jiffies_module_exit(void)
{
    proc_remove(jiff_dir_entry);
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);
