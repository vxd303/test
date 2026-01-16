#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/printk.h>

static struct kobject *chipid_kobj;

static ssize_t m_id_show(struct kobject *kobj,
                         struct kobj_attribute *attr, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "202025\n");
}

static struct kobj_attribute m_id_attr =
	__ATTR(m_id, 0444, m_id_show, NULL);

static int __init chipid_init(void)
{
	int ret;

	if (!system_kobj) {
		pr_err("CHIPID: system_kobj NULL\n");
		return -ENODEV;
	}

	chipid_kobj = kobject_create_and_add("chip-id", system_kobj);
	if (!chipid_kobj)
		return -ENOMEM;

	ret = sysfs_create_file(chipid_kobj, &m_id_attr.attr);
	if (ret) {
		kobject_put(chipid_kobj);
		return ret;
	}

	pr_info("CHIPID: /sys/devices/system/chip-id/m_id created\n");
	return 0;
}

subsys_initcall(chipid_init);
