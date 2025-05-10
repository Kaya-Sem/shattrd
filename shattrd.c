#include "linux/netlink.h"
#include "linux/printk.h"
#include "net/netlink.h"
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <net/sock.h>

/* Message types */
#define MSG_TYPE (0x10 + 2)
#define MSG_TYPE_TEST (0x10 + 4)
#define MSG_TYPE_SET_PASSWD (0x10 + 2)

static struct sock *my_nl_sock;

static int rcv_msg_handler(struct sk_buff* skb, struct nlmsghdr *nlh) {
  int type;
  char *data;

  type = nlh->nlmsg_type;

  switch (type) {
  case MSG_TYPE_SET_PASSWD:
    printk("MSG_TYPE_SET_PASSWD called");
    break;
  case MSG_TYPE_TEST:
    size_t num_bytes = nlh->nlmsg_len - NLMSG_HDRLEN;
    data = NLMSG_DATA(nlh); /* pointer to first byte */

    for (size_t i = 0; i < num_bytes; i++) {
      printk("%02x", data[i]);
    }
    printk("\n");
  default:
    printk("Unknown message type received: %d", type);
  }

  return 0;
}

static void nl_rcv_msg(struct sk_buff *skb) {
	netlink_rcv_skb(skb, &rcv_msg_handler);
}

MODULE_AUTHOR("Kaya-Sem");
MODULE_DESCRIPTION("Immutability Enforcement Module");
MODULE_LICENSE("GPL"); // Custom init and exit methods

static int __init custom_init(void) {
  printk(KERN_INFO "[SHATTRD] Module loaded");
	my_nl_sock = netlink_kernel_create(&init_net, NETLINK_USERSOCK, 0, netlink_rcv_skb())


  return 0;
}

static void __exit custom_exit(void) {
  printk(KERN_INFO "[SHATTRD] Unloaded module");
}

/* Leave out the custom_exit if you do not want the ability to unload the module
 */
module_exit(custom_exit);
module_init(custom_init);
