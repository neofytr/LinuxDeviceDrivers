#include <linux/module.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("neofyt (rajisbornforcoc@gmail.com)");
MODULE_DESCRIPTION("Basic read loadable kernel module");

#define MAX_SIZE 512

char msg[MAX_SIZE] = "Hello, World, Let's Go\n";

static struct proc_dir_entry *custom_proc_node;
static struct proc_ops neo_proc_ops;
static ssize_t neo_read(struct file *file_ptr, char *user_space_buffer, size_t count, loff_t *offset);
ssize_t neo_write(struct file *, const char *, size_t, loff_t *);

ssize_t neo_write(struct file *file_ptr, const char *user_space_buffer, size_t count, loff_t *offset)
{
    if (count > MAX_SIZE)
        count = MAX_SIZE;

    if (*offset + count > MAX_SIZE)
        count = MAX_SIZE - *offset;

    if (copy_from_user(msg + *offset, user_space_buffer, count))
        return -EFAULT;

    *offset += count;
    return count;
}

static ssize_t neo_read(struct file *file_ptr, char *user_space_buffer, size_t count, loff_t *offset) // user_space_buffer contains the bytes that are read from the "file"
{
    size_t len = strlen(msg);
    if (*offset >= len)
        return 0;

    if (*offset + count > len)
        count = len - *offset;

    if (copy_to_user(user_space_buffer, msg + *offset, count))
        return -EFAULT;

    *offset += count;
    return count; // return the number of bytes read from the "file"
}

static int neo_module_init(void)
{
    neo_proc_ops.proc_read = neo_read; // binding neo_read function to read on /proc/neo
    neo_proc_ops.proc_write = neo_write;

    // NULL in the 3rd argument creates the new file in the root of the proc directory
    custom_proc_node = proc_create("neo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, NULL, &neo_proc_ops);
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
