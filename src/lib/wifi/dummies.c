/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Josef Soentgen
 * \date   2022-02-09
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>


#include <linux/types.h>

const u8 shipped_regdb_certs[] = { };
unsigned int shipped_regdb_certs_len = sizeof (shipped_regdb_certs);


#include <linux/filter.h>
#include <linux/jump_label.h> /* for DEFINE_STATIC_KEY_FALSE */

void bpf_prog_change_xdp(struct bpf_prog *prev_prog, struct bpf_prog *prog)
{
	lx_emul_trace(__func__);
}

DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);


asmlinkage __wsum csum_partial(const void * buff,int len,__wsum sum)
{
	lx_emul_trace_and_stop(__func__);
}


struct static_key_false init_on_alloc;


#include <linux/proc_ns.h>

int proc_alloc_inum(unsigned int * inum)
{
	*inum = 1; /* according to linux/proc_ns.h without CONFIG_PROC_FS */
	return 0;
}


#include <net/net_namespace.h>

__init int net_sysctl_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/fs.h>

unsigned int get_next_ino(void)
{
	static unsigned int count = 0;
	return ++count;
}


#include <linux/netdevice.h>

int __init dev_proc_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/stringhash.h>

unsigned int full_name_hash(const void * salt,const char * name,unsigned int len)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/key.h>

struct key * keyring_alloc(const char * description,kuid_t uid,kgid_t gid,const struct cred * cred,key_perm_t perm,unsigned long flags,struct key_restriction * restrict_link,struct key * dest)
{
	static struct key _key;
	lx_emul_trace(__func__);
	return &_key;
}


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/moduleparam.h>

void kernel_param_lock(struct module * mod)
{
	lx_emul_trace(__func__);
}


#include <linux/moduleparam.h>

void kernel_param_unlock(struct module * mod)
{
	lx_emul_trace(__func__);
}


#include <linux/pid.h>

void put_pid(struct pid * pid)
{
	lx_emul_trace(__func__);
}


#include <linux/filter.h>

int sk_filter_trim_cap(struct sock * sk,struct sk_buff * skb,unsigned int cap)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/capability.h>

bool file_ns_capable(const struct file * file,struct user_namespace * ns,int cap)
{
	lx_emul_trace(__func__);
	return true;
}


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace(__func__);
}


#include <linux/skbuff.h>

void __skb_get_hash(struct sk_buff * skb)
{
	lx_emul_trace(__func__);
}


#include <linux/pid.h>

pid_t pid_vnr(struct pid * pid)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/verification.h>

int verify_pkcs7_signature(const void *data, size_t len,
               const void *raw_pkcs7, size_t pkcs7_len,
               struct key *trusted_keys,
               enum key_being_used_for usage,
               int (*view_content)(void *ctx,
                           const void *data, size_t len,
                           size_t asn1hdrlen),
               void *ctx)
{
	return true;
}


#include <linux/pci.h>

void pci_lock_rescan_remove(void)
{
	lx_emul_trace(__func__);
}


void pci_unlock_rescan_remove(void)
{
	lx_emul_trace(__func__);
}


bool pci_pme_capable(struct pci_dev *dev, pci_power_t state)
{
	lx_emul_trace(__func__);
	return false;
}


int pcie_capability_read_word(struct pci_dev *dev, int pos, u16 *val)
{
	lx_emul_trace(__func__);
	return -1;
}


u16 pci_find_ext_capability(struct pci_dev *dev, int cap)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/net.h>

int net_ratelimit(void)
{
	lx_emul_trace(__func__);
	/* suppress */
	return 0;
}


#include <asm/smp.h>

void synchronize_rcu_expedited(void)
{
	lx_emul_trace(__func__);
}


#include <linux/pci.h>

int pci_enable_msi(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
	return -ENOSYS;
}


void pci_disable_msi(struct pci_dev *dev)
{
    lx_emul_trace(__func__);
}


int pci_enable_msix_range(struct pci_dev *dev, struct msix_entry *entries,
                          int minvec, int maxvec)
{
	lx_emul_trace(__func__);
	return -ENOSYS;
}


void pci_disable_device(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
}


int pcim_iomap_regions(struct pci_dev *pdev, int mask, const char *name)
{
	lx_emul_trace(__func__);
	return 0;
}


int pcie_capability_clear_and_set_word(struct pci_dev *dev, int pos,
                                       u16 clear, u16 set)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/netdevice.h>

int dev_ioctl(struct net *net, unsigned int cmd, struct ifreq *ifr, bool *need_copyout)
{
	lx_emul_trace_and_stop(__func__);
}


int get_option(char ** str,int * pint)
{
	lx_emul_trace_and_stop(__func__);
}


char * get_options(const char * str,int nints,int * ints)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of_fdt.h>

bool __init early_init_dt_scan(void * params)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/of_fdt.h>

void __init unflatten_device_tree(void)
{
	lx_emul_trace(__func__);
}


#include <linux/of_irq.h>

void __init of_irq_init(const struct of_device_id * matches)
{
	lx_emul_trace(__func__);
}


#include <linux/of.h>

void __init of_core_init(void)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

void rcu_barrier(void)
{
	lx_emul_trace(__func__);
}


#include <linux/srcu.h>

void synchronize_srcu(struct srcu_struct * ssp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of_clk.h>

void __init of_clk_init(const struct of_device_id * matches)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

void add_device_randomness(const void * buf,unsigned int size)
{
	lx_emul_trace(__func__);
}


extern void register_irq_proc(unsigned int irq,struct irq_desc * desc);
void register_irq_proc(unsigned int irq,struct irq_desc * desc)
{
	lx_emul_trace(__func__);
}


extern void register_handler_proc(unsigned int irq,struct irqaction * action);
void register_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


#include <linux/of.h>

bool of_device_is_available(const struct device_node * device)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/random.h>

void add_interrupt_randomness(int irq,int irq_flags)
{
	lx_emul_trace(__func__);
}


#include <linux/skbuff.h>

bool __skb_flow_dissect(const struct net * net,const struct sk_buff * skb,struct flow_dissector * flow_dissector,void * target_container,const void * data,__be16 proto,int nhoff,int hlen,unsigned int flags)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/pci.h>

int pci_disable_link_state(struct pci_dev * pdev,int state)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/dma-map-ops.h>

bool dma_default_coherent = false;


/***********************************
 ** Common dummies from repos/imx **
 ***********************************/

unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n);
unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n);
unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpuhotplug.h>

int __cpuhp_setup_state(enum cpuhp_state state,const char * name,bool invoke,int (* startup)(unsigned int cpu),int (* teardown)(unsigned int cpu),bool multi_instance)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <asm-generic/sections.h>

char __end_rodata[]   = {};


#include <asm-generic/sections.h>

char __start_rodata[] = {};


#include <linux/kernel_stat.h>

void account_process_tick(struct task_struct * p,int user_tick)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

int add_random_ready_callback(struct random_ready_callback * rdy)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sched/loadavg.h>

void calc_global_load(void)
{
	lx_emul_trace(__func__);
}


#include <linux/tracepoint-defs.h>

const struct trace_print_flags gfpflag_names[]  = { {0,NULL}};


#include <linux/sched/signal.h>

void ignore_signals(struct task_struct * t)
{
	lx_emul_trace(__func__);
}


#include <linux/kernfs.h>

void kernfs_get(struct kernfs_node * kn) { }


unsigned long net_rand_noise;


#include <linux/tracepoint-defs.h>

const struct trace_print_flags pageflag_names[] = { {0,NULL}};


#include <linux/kernel.h>

bool parse_option_str(const char *str, const char *option)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/proc_fs.h>

struct proc_dir_entry { int dummy; };

struct proc_dir_entry * proc_create_net_data(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	static struct proc_dir_entry _proc_dir_entry;
	lx_emul_trace(__func__);
	return &_proc_dir_entry;
}


struct proc_dir_entry * proc_create_seq_private(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	static struct proc_dir_entry ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/rcupdate.h>

void rcu_sched_clock_irq(int user)
{
	lx_emul_trace(__func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/property.h>

int software_node_notify(struct device * dev,unsigned long action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/timekeeper_internal.h>

void update_vsyscall(struct timekeeper * tk)
{
	lx_emul_trace(__func__);
}


u64 vabits_actual;
EXPORT_SYMBOL(vabits_actual);


#include <linux/tracepoint-defs.h>

const struct trace_print_flags vmaflag_names[]  = { {0,NULL}};
