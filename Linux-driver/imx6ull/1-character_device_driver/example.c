/*******************************************************
 * @Author: Hu Yao
 * @Date: 2026-02-03 19:58:28
 * @LastEditTime: 2026-02-03 20:24:14
 * @LastEditors: Hu Yao
 * @Version:0.1
 * @Description:字符设备驱动示例
 * @Copyright(c) 2025 - 2030 SINEE.All rights reserved
 *******************************************************/
#include <linux/module.h>

#define DEVICE_NAME "example_device"
#define DEVICE_MAJOR 240

static struct file_operations fops;

static int __init example_init(void)
{
    int ret;
    ret = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);
    if (ret < 0)
    {
        printk("Failed to register character device\n");
        return ret;
    }
}
static void __exit example_exit(void)
{
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
}
module_init(example_init);
module_exit(example_exit);