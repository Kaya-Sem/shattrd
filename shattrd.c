#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/netlink.h>
#include <linux/proc_fs.h>

MODULE_AUTHOR("Kaya-Sem");
MODULE_DESCRIPTION("Immutability Enforcement Module");
MODULE_LICENSE("GPL");// Custom init and exit methods


static int __init custom_init(void) {
 printk(KERN_INFO "[SHATTRD] Module loaded");

 return 0;
}


static void __exit custom_exit(void) {
 printk(KERN_INFO "[SHATTRD] Unloaded module");
}


/* Leave out the custom_exit if you do not want the ability to unload the module */
module_exit(custom_exit);
module_init(custom_init);
