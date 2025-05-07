#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>// Module metadata

MODULE_AUTHOR("Kaya-Sem");
MODULE_DESCRIPTION("Immutability Enforcement Module");
MODULE_LICENSE("GPL");// Custom init and exit methods


static int __init custom_init(void) {
 printk(KERN_INFO "[INIT] Hello world driver loaded.");
 return 0;
}


static void __exit custom_exit(void) {
 printk(KERN_INFO "Goodbye my friend, I shall miss you dearly...");
}


module_init(custom_init);
module_exit(custom_exit);
