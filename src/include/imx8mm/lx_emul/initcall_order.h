/*
 * \brief  Array defining order of Linux Kernel initcalls
 * \author Automatically generated file - do no edit
 * \date   2021-06-09
 */

#ifndef _LX_EMUL__INITCALL_ORDER_H_
#define _LX_EMUL__INITCALL_ORDER_H_

static const char * lx_emul_initcall_order[] = {
	"__initcall_start",
	"__initcall_trace_init_flags_sys_enterearly",
	"__initcall_trace_init_flags_sys_exitearly",
	"__initcall_cpu_suspend_initearly",
	"__initcall_asids_initearly",
	"__initcall_xen_guest_initearly",
	"__initcall_spawn_ksoftirqdearly",
	"__initcall_migration_initearly",
	"__initcall_srcu_bootup_announceearly",
	"__initcall_rcu_spawn_core_kthreadsearly",
	"__initcall_rcu_spawn_gp_kthreadearly",
	"__initcall_check_cpu_stall_initearly",
	"__initcall_rcu_sysrq_initearly",
	"__initcall_cpu_stop_initearly",
	"__initcall_init_kprobesearly",
	"__initcall_init_eventsearly",
	"__initcall_init_trace_printkearly",
	"__initcall_event_trace_enable_againearly",
	"__initcall_jump_label_init_moduleearly",
	"__initcall_dynamic_debug_initearly",
	"__initcall_initialize_ptr_randomearly",
	"__initcall_its_pmsi_initearly",
	"__initcall_its_pci_msi_initearly",
	"__initcall_efi_memreserve_root_initearly",
	"__initcall_arm_enable_runtime_servicesearly",
	"__initcall_efi_earlycon_remap_fbearly",
	"__initcall_dummy_timer_registerearly",
	"__initcall_idle_inject_initearly",
	"__initcall_bpf_jit_charge_init0",
	"__initcall_memory_stats_init0",
	"__initcall_ipc_ns_init0",
	"__initcall_init_mmap_min_addr0",
	"__initcall_pci_realloc_setup_params0",
	"__initcall_net_ns_init0",
	"__initcall_inet_frag_wq_init0",
	"__initcall_fpsimd_init1",
	"__initcall_tagged_addr_init1",
	"__initcall_enable_mrs_emulation1",
	"__initcall_armv8_deprecated_init1",
	"__initcall_kaslr_init1",
	"__initcall_map_entry_trampoline1",
	"__initcall_alloc_frozen_cpus1",
	"__initcall_cpu_hotplug_pm_sync_init1",
	"__initcall_wq_sysfs_init1",
	"__initcall_ksysfs_init1",
	"__initcall_schedutil_gov_init1",
	"__initcall_pm_init1",
	"__initcall_pm_disk_init1",
	"__initcall_swsusp_header_init1",
	"__initcall_rcu_set_runtime_mode1",
	"__initcall_dma_init_reserved_memory1",
	"__initcall_init_jiffies_clocksource1",
	"__initcall_futex_init1",
	"__initcall_cgroup_wq_init1",
	"__initcall_cgroup1_wq_init1",
	"__initcall_ftrace_mod_cmd_init1",
	"__initcall_init_graph_trace1",
	"__initcall_init_kprobe_trace_early1",
	"__initcall_cpu_pm_init1",
	"__initcall_init_zero_pfn1",
	"__initcall_mem_cgroup_swap_init1",
	"__initcall_memory_failure_init1",
	"__initcall_cma_init_reserved_areas1",
	"__initcall_fsnotify_init1",
	"__initcall_filelock_init1",
	"__initcall_init_misc_binfmt1",
	"__initcall_init_script_binfmt1",
	"__initcall_init_elf_binfmt1",
	"__initcall_init_compat_elf_binfmt1",
	"__initcall_debugfs_init1",
	"__initcall_tracefs_init1",
	"__initcall_securityfs_init1",
	"__initcall_prandom_init_early1",
	"__initcall_pinctrl_init1",
	"__initcall_gpiolib_dev_init1",
	"__initcall_fsl_guts_init1",
	"__initcall_virtio_init1",
	"__initcall_regulator_init1",
	"__initcall_iommu_init1",
	"__initcall_component_debug_init1",
	"__initcall_genpd_bus_init1",
	"__initcall_soc_bus_register1",
	"__initcall_register_cpufreq_notifier1",
	"__initcall_opp_debug_init1",
	"__initcall_cpufreq_core_init1",
	"__initcall_cpufreq_gov_performance_init1",
	"__initcall_cpufreq_gov_powersave_init1",
	"__initcall_cpufreq_gov_userspace_init1",
	"__initcall_CPU_FREQ_GOV_ONDEMAND_init1",
	"__initcall_CPU_FREQ_GOV_CONSERVATIVE_init1",
	"__initcall_cpufreq_dt_platdev_init1",
	"__initcall_cpuidle_init1",
	"__initcall_arm_dmi_init1",
	"__initcall_sock_init1",
	"__initcall_net_inuse_init1",
	"__initcall_net_defaults_init1",
	"__initcall_init_default_flow_dissectors1",
	"__initcall_netlink_proto_init1",
	"__initcall_genl_init1",
	"__initcall___gnttab_init1s",
	"__initcall_debug_monitors_init2",
	"__initcall_irq_sysfs_init2",
	"__initcall_dma_atomic_pool_init2",
	"__initcall_audit_init2",
	"__initcall_release_early_probes2",
	"__initcall_bdi_class_init2",
	"__initcall_mm_sysfs_init2",
	"__initcall_init_per_zone_wmark_min2",
	"__initcall_mpi_init2",
	"__initcall_kobject_uevent_init2",
	"__initcall_gpiolib_sysfs_init2",
	"__initcall_pcibus_class_init2",
	"__initcall_pci_driver_init2",
	"__initcall_backlight_class_init2",
	"__initcall_amba_init2",
	"__initcall_xenbus_init2",
	"__initcall_anatop_regulator_init2",
	"__initcall_tty_class_init2",
	"__initcall_vtconsole_class_init2",
	"__initcall_serdev_init2",
	"__initcall_iommu_dev_init2",
	"__initcall_mipi_dsi_bus_init2",
	"__initcall_devlink_class_init2",
	"__initcall_software_node_init2",
	"__initcall_wakeup_sources_debugfs_init2",
	"__initcall_wakeup_sources_sysfs_init2",
	"__initcall_register_node_type2",
	"__initcall_regmap_initcall2",
	"__initcall_syscon_init2",
	"__initcall_spi_init2",
	"__initcall_i2c_init2",
	"__initcall_thermal_init2",
	"__initcall_init_ladder2",
	"__initcall_init_menu2",
	"__initcall_rpmsg_init2",
	"__initcall_rpmsg_ns_init2",
	"__initcall_reserve_memblock_reserved_regions3",
	"__initcall_aarch32_alloc_vdso_pages3",
	"__initcall_vdso_init3",
	"__initcall_arch_hw_breakpoint_init3",
	"__initcall_asids_update_limit3",
	"__initcall_hugetlbpage_init3",
	"__initcall_p2m_init3",
	"__initcall_xen_mm_init3",
	"__initcall_kcmp_cookies_init3",
	"__initcall_cryptomgr_init3",
	"__initcall_imx8mq_pinctrl_init3",
	"__initcall_dma_channel_table_init3",
	"__initcall_dma_bus_init3",
	"__initcall_register_xen_platform_notifier3",
	"__initcall_register_xen_amba_notifier3",
	"__initcall_register_xen_pci_notifier3",
	"__initcall_pl011_init3",
	"__initcall_iommu_dma_init3",
	"__initcall_dmi_id_init3",
	"__initcall_of_platform_default_populate_init3s",
	"__initcall_topology_init4",
	"__initcall_uid_cache_init4",
	"__initcall_param_sysfs_init4",
	"__initcall_user_namespace_sysctl_init4",
	"__initcall_proc_schedstat_init4",
	"__initcall_pm_sysrq_init4",
	"__initcall_create_proc_profile4",
	"__initcall_time_ns_init4",
	"__initcall_crash_save_vmcoreinfo_init4",
	"__initcall_crash_notes_memory_init4",
	"__initcall_cgroup_sysfs_init4",
	"__initcall_cgroup_namespaces_init4",
	"__initcall_user_namespaces_init4",
	"__initcall_hung_task_init4",
	"__initcall_send_signal_irq_work_init4",
	"__initcall_dev_map_init4",
	"__initcall_cpu_map_init4",
	"__initcall_netns_bpf_init4",
	"__initcall_stack_map_init4",
	"__initcall_oom_init4",
	"__initcall_default_bdi_init4",
	"__initcall_cgwb_init4",
	"__initcall_percpu_enable_async4",
	"__initcall_kcompactd_init4",
	"__initcall_init_user_reserve4",
	"__initcall_init_admin_reserve4",
	"__initcall_init_reserve_notifier4",
	"__initcall_swap_init_sysfs4",
	"__initcall_swapfile_init4",
	"__initcall_hugetlb_init4",
	"__initcall_ksm_init4",
	"__initcall_hugepage_init4",
	"__initcall_mem_cgroup_init4",
	"__initcall_io_wq_init4",
	"__initcall_fips_init4",
	"__initcall_seqiv_module_init4",
	"__initcall_echainiv_module_init4",
	"__initcall_dh_init4",
	"__initcall_rsa_init4",
	"__initcall_crypto_cmac_module_init4",
	"__initcall_hmac_module_init4",
	"__initcall_crypto_null_mod_init4",
	"__initcall_md5_mod_init4",
	"__initcall_sha1_generic_mod_init4",
	"__initcall_sha256_generic_mod_init4",
	"__initcall_sha3_generic_mod_init4",
	"__initcall_streebog_mod_init4",
	"__initcall_crypto_ecb_module_init4",
	"__initcall_crypto_cbc_module_init4",
	"__initcall_xts_module_init4",
	"__initcall_crypto_ctr_module_init4",
	"__initcall_crypto_gcm_module_init4",
	"__initcall_crypto_ccm_module_init4",
	"__initcall_pcrypt_init4",
	"__initcall_cryptd_init4",
	"__initcall_des_generic_mod_init4",
	"__initcall_blowfish_mod_init4",
	"__initcall_aes_init4",
	"__initcall_arc4_init4",
	"__initcall_deflate_mod_init4",
	"__initcall_crc32c_mod_init4",
	"__initcall_crct10dif_mod_init4",
	"__initcall_crypto_authenc_module_init4",
	"__initcall_crypto_authenc_esn_module_init4",
	"__initcall_lzo_mod_init4",
	"__initcall_lzorle_mod_init4",
	"__initcall_prng_mod_init4",
	"__initcall_drbg_init4",
	"__initcall_ghash_mod_init4",
	"__initcall_essiv_module_init4",
	"__initcall_curve25519_init4",
	"__initcall_ecdh_init4",
	"__initcall_init_bio4",
	"__initcall_blk_settings_init4",
	"__initcall_blk_ioc_init4",
	"__initcall_blk_mq_init4",
	"__initcall_genhd_device_init4",
	"__initcall_blkcg_init4",
	"__initcall_irq_poll_setup4",
	"__initcall_gpiolib_debugfs_init4",
	"__initcall_gpio_mxc_init4",
	"__initcall_pca953x_init4",
	"__initcall_pwm_debugfs_init4",
	"__initcall_pwm_sysfs_init4",
	"__initcall_pci_slot_init4",
	"__initcall_fbmem_init4",
	"__initcall_ipu_init4",
	"__initcall_balloon_init4",
	"__initcall_xen_setup_shutdown_event4",
	"__initcall_regulator_fixed_voltage_init4",
	"__initcall_gpio_regulator_init4",
	"__initcall_misc_init4",
	"__initcall_iommu_subsys_init4",
	"__initcall_cn_init4",
	"__initcall_register_cpu_capacity_sysctl4",
	"__initcall_dma_buf_init4",
	"__initcall_dma_heap_init4",
	"__initcall_init_scsi4",
	"__initcall_phy_init4",
	"__initcall_usb_common_init4",
	"__initcall_ulpi_init4",
	"__initcall_usb_init4",
	"__initcall_usb_roles_init4",
	"__initcall_serio_init4",
	"__initcall_input_init4",
	"__initcall_rtc_init4",
	"__initcall_i2c_adap_imx_init4",
	"__initcall_media_devnode_init4",
	"__initcall_videodev_init4",
	"__initcall_init_dvbdev4",
	"__initcall_cec_devnode_init4",
	"__initcall_power_supply_class_init4",
	"__initcall_hwmon_init4",
	"__initcall_md_init4",
	"__initcall_psci_idle_init_domains4",
	"__initcall_mmc_init4",
	"__initcall_leds_init4",
	"__initcall_dmi_init4",
	"__initcall_efisubsys_init4",
	"__initcall_register_gop_device4",
	"__initcall_rpmsg_init4",
	"__initcall_devfreq_init4",
	"__initcall_devfreq_simple_ondemand_init4",
	"__initcall_devfreq_userspace_init4",
	"__initcall_arm_pmu_hp_init4",
	"__initcall_ras_init4",
	"__initcall_nvmem_init4",
	"__initcall_mux_init4",
	"__initcall_init_soundcore4",
	"__initcall_alsa_sound_init4",
	"__initcall_alsa_seq_device_init4",
	"__initcall_imx_audmux_init4",
	"__initcall_ac97_bus_init4",
	"__initcall_proto_init4",
	"__initcall_net_dev_init4",
	"__initcall_neigh_init4",
	"__initcall_fib_notifier_init4",
	"__initcall_fib_rules_init4",
	"__initcall_init_cgroup_netprio4",
	"__initcall_bpf_lwt_init4",
	"__initcall_ethnl_init4",
	"__initcall_nexthop_init4",
	"__initcall_bt_init4",
	"__initcall_ieee80211_init4",
	"__initcall_rfkill_init4",
	"__initcall_watchdog_init4s",
	"__initcall_create_debug_debugfs_entry5",
	"__initcall_clocksource_done_booting5",
	"__initcall_tracer_init_tracefs5",
	"__initcall_init_trace_printk_function_export5",
	"__initcall_init_graph_tracefs5",
	"__initcall_bpf_event_init5",
	"__initcall_init_kprobe_trace5",
	"__initcall_init_dynamic_event5",
	"__initcall_init_uprobe_trace5",
	"__initcall_bpf_init5",
	"__initcall_init_pipe_fs5",
	"__initcall_cgroup_writeback_init5",
	"__initcall_inotify_user_setup5",
	"__initcall_eventpoll_init5",
	"__initcall_anon_inode_init5",
	"__initcall_proc_locks_init5",
	"__initcall_iomap_init5",
	"__initcall_dquot_init5",
	"__initcall_quota_init5",
	"__initcall_proc_cmdline_init5",
	"__initcall_proc_consoles_init5",
	"__initcall_proc_cpuinfo_init5",
	"__initcall_proc_devices_init5",
	"__initcall_proc_interrupts_init5",
	"__initcall_proc_loadavg_init5",
	"__initcall_proc_meminfo_init5",
	"__initcall_proc_stat_init5",
	"__initcall_proc_uptime_init5",
	"__initcall_proc_version_init5",
	"__initcall_proc_softirqs_init5",
	"__initcall_proc_kcore_init5",
	"__initcall_vmcore_init5",
	"__initcall_proc_kmsg_init5",
	"__initcall_proc_page_init5",
	"__initcall_fscache_init5",
	"__initcall_init_ramfs_fs5",
	"__initcall_init_hugetlbfs_fs5",
	"__initcall_cachefiles_init5",
	"__initcall_aa_create_aafs5",
	"__initcall_blk_scsi_ioctl_init5",
	"__initcall_dynamic_debug_init_control5",
	"__initcall_simplefb_init5",
	"__initcall_chr_dev_init5",
	"__initcall_firmware_class_init5",
	"__initcall_ssb_modinit5",
	"__initcall_bcma_init_bus_register5",
	"__initcall_powercap_init5",
	"__initcall_sysctl_core_init5",
	"__initcall_eth_offload_init5",
	"__initcall_ipv4_offload_init5",
	"__initcall_inet_init5",
	"__initcall_af_unix_init5",
	"__initcall_ipv6_offload_init5",
	"__initcall_cfg80211_init5",
	"__initcall_pci_apply_final_quirks5s",
	"__initcall_populate_rootfsrootfs",
	"__initcall_register_arm64_panic_block6",
	"__initcall_cpuinfo_regs_init6",
	"__initcall_armv8_pmu_driver_init6",
	"__initcall_arch_init_uprobes6",
	"__initcall_ptdump_init6",
	"__initcall_arm_init6",
	"__initcall_cpu_feature_match_SHA1_init6",
	"__initcall_cpu_feature_match_SHA2_init6",
	"__initcall_cpu_feature_match_SHA512_init6",
	"__initcall_cpu_feature_match_SHA3_init6",
	"__initcall_cpu_feature_match_AES_init6",
	"__initcall_aes_mod_init6",
	"__initcall_cpu_feature_match_AES_init6",
	"__initcall_aes_init6",
	"__initcall_sha256_mod_init6",
	"__initcall_sha512_mod_init6",
	"__initcall_chacha_simd_mod_init6",
	"__initcall_neon_poly1305_mod_init6",
	"__initcall_aes_init6",
	"__initcall_proc_execdomains_init6",
	"__initcall_register_warn_debugfs6",
	"__initcall_cpuhp_sysfs_init6",
	"__initcall_ioresources_init6",
	"__initcall_init_sched_debug_procfs6",
	"__initcall_snapshot_device_init6",
	"__initcall_irq_gc_init_ops6",
	"__initcall_irq_pm_init_ops6",
	"__initcall_irq_debugfs_init6",
	"__initcall_timekeeping_init_ops6",
	"__initcall_init_clocksource_sysfs6",
	"__initcall_init_timer_list_procfs6",
	"__initcall_alarmtimer_init6",
	"__initcall_init_posix_timers6",
	"__initcall_clockevents_init_sysfs6",
	"__initcall_sched_clock_syscore_init6",
	"__initcall_proc_modules_init6",
	"__initcall_kallsyms_init6",
	"__initcall_pid_namespaces_init6",
	"__initcall_ikconfig_init6",
	"__initcall_audit_watch_init6",
	"__initcall_audit_fsnotify_init6",
	"__initcall_audit_tree_init6",
	"__initcall_seccomp_sysctl_init6",
	"__initcall_utsname_sysctl_init6",
	"__initcall_init_tracepoints6",
	"__initcall_stack_trace_init6",
	"__initcall_init_blk_tracer6",
	"__initcall_perf_event_sysfs_init6",
	"__initcall_system_trusted_keyring_init6",
	"__initcall_kswapd_init6",
	"__initcall_extfrag_debug_init6",
	"__initcall_mm_compute_batch_init6",
	"__initcall_slab_proc_init6",
	"__initcall_workingset_init6",
	"__initcall_proc_vmalloc_init6",
	"__initcall_memblock_init_debugfs6",
	"__initcall_procswaps_init6",
	"__initcall_init_frontswap6",
	"__initcall_slab_sysfs_init6",
	"__initcall_init_zbud6",
	"__initcall_fcntl_init6",
	"__initcall_proc_filesystems_init6",
	"__initcall_start_dirtytime_writeback6",
	"__initcall_blkdev_init6",
	"__initcall_dio_init6",
	"__initcall_dnotify_init6",
	"__initcall_fanotify_user_setup6",
	"__initcall_userfaultfd_init6",
	"__initcall_aio_setup6",
	"__initcall_io_uring_init6",
	"__initcall_mbcache_init6",
	"__initcall_init_devpts_fs6",
	"__initcall_ext4_init_fs6",
	"__initcall_journal_init6",
	"__initcall_init_squashfs_fs6",
	"__initcall_init_fat_fs6",
	"__initcall_init_vfat_fs6",
	"__initcall_init_msdos_fs6",
	"__initcall_init_exfat_fs6",
	"__initcall_init_iso9660_fs6",
	"__initcall_init_nls_cp4376",
	"__initcall_init_nls_cp7376",
	"__initcall_init_nls_cp7756",
	"__initcall_init_nls_cp8506",
	"__initcall_init_nls_cp8526",
	"__initcall_init_nls_cp8556",
	"__initcall_init_nls_cp8576",
	"__initcall_init_nls_cp8606",
	"__initcall_init_nls_cp8616",
	"__initcall_init_nls_cp8626",
	"__initcall_init_nls_cp8636",
	"__initcall_init_nls_cp8646",
	"__initcall_init_nls_cp8656",
	"__initcall_init_nls_cp8666",
	"__initcall_init_nls_cp8696",
	"__initcall_init_nls_cp12506",
	"__initcall_init_nls_cp12516",
	"__initcall_init_nls_ascii6",
	"__initcall_init_nls_iso8859_16",
	"__initcall_init_nls_utf86",
	"__initcall_init_ntfs_fs6",
	"__initcall_init_affs_fs6",
	"__initcall_fuse_init6",
	"__initcall_virtio_fs_init6",
	"__initcall_ovl_init6",
	"__initcall_init_udf_fs6",
	"__initcall_ipc_init6",
	"__initcall_ipc_sysctl_init6",
	"__initcall_init_mqueue_fs6",
	"__initcall_key_proc_init6",
	"__initcall_apparmor_nf_ip_init6",
	"__initcall_crypto_algapi_init6",
	"__initcall_jent_mod_init6",
	"__initcall_af_alg_init6",
	"__initcall_algif_hash_init6",
	"__initcall_algif_skcipher_init6",
	"__initcall_rng_init6",
	"__initcall_algif_aead_init6",
	"__initcall_ecrdsa_mod_init6",
	"__initcall_asymmetric_key_init6",
	"__initcall_x509_key_init6",
	"__initcall_proc_genhd_init6",
	"__initcall_bsg_init6",
	"__initcall_throtl_init6",
	"__initcall_deadline_init6",
	"__initcall_kyber_init6",
	"__initcall_bfq_init6",
	"__initcall_mod_init6",
	"__initcall_mod_init6",
	"__initcall_mod_init6",
	"__initcall_crc_t10dif_mod_init6",
	"__initcall_libcrc32c_mod_init6",
	"__initcall_percpu_counter_startup6",
	"__initcall_audit_classes_init6",
	"__initcall_sg_pool_init6",
	"__initcall_imx_irqsteer_driver_init6",
	"__initcall_imx_intmux_driver_init6",
	"__initcall_phy_core_init6",
	"__initcall_imx8mq_usb_phy_driver_init6",
	"__initcall_mixel_dphy_driver_init6",
	"__initcall_imx_pwm_driver_init6",
	"__initcall_pcie_portdrv_init6",
	"__initcall_pci_proc_init6",
	"__initcall_gen_pci_driver_init6",
	"__initcall_imx6_pcie_init6",
	"__initcall_gpio_backlight_driver_init6",
	"__initcall_pwm_backlight_driver_init6",
	"__initcall_led_bl_driver_init6",
	"__initcall_dlfb_driver_init6",
	"__initcall_efifb_driver_init6",
	"__initcall_of_fixed_factor_clk_driver_init6",
	"__initcall_of_fixed_clk_driver_init6",
	"__initcall_gpio_clk_driver_init6",
	"__initcall_imx8mq_clk_driver_init6",
	"__initcall_sdma_driver_init6",
	"__initcall_imx_pgc_domain_driver_init6",
	"__initcall_imx_gpc_driver_init6",
	"__initcall_imx8_soc_init6",
	"__initcall_virtio_mmio_init6",
	"__initcall_virtio_pci_driver_init6",
	"__initcall_virtio_balloon_driver_init6",
	"__initcall_virtio_input_driver_init6",
	"__initcall_xenbus_probe_initcall6",
	"__initcall_xenbus_init6",
	"__initcall_regulator_virtual_consumer_driver_init6",
	"__initcall_regulator_userspace_consumer_driver_init6",
	"__initcall_fan53555_regulator_driver_init6",
	"__initcall_pfuze_driver_init6",
	"__initcall_pwm_regulator_driver_init6",
	"__initcall_vctrl_driver_init6",
	"__initcall_imx7_reset_driver_init6",
	"__initcall_n_null_init6",
	"__initcall_pty_init6",
	"__initcall_sysrq_init6",
	"__initcall_pl010_init6",
	"__initcall_imx_uart_init6",
	"__initcall_init_kgdboc6",
	"__initcall_init6",
	"__initcall_hwrng_modinit6",
	"__initcall_virtio_rng_driver_init6",
	"__initcall_virtio_iommu_drv_init6",
	"__initcall_drm_kms_helper_init6",
	"__initcall_drm_core_init6",
	"__initcall_drm_sched_fence_slab_init6",
	"__initcall_virtio_gpu_driver_init6",
	"__initcall_dcss_platform_driver_init6",
	"__initcall_cdns_mhdp_imx_platform_driver_init6",
	"__initcall_panel_lvds_driver_init6",
	"__initcall_panel_simple_init6",
	"__initcall_display_connector_driver_init6",
	"__initcall_lvds_codec_driver_init6",
	"__initcall_simple_bridge_driver_init6",
	"__initcall_ti_sn_bridge_driver_init6",
	"__initcall_nwl_dsi_driver_init6",
	"__initcall_mhdp_driver_init6",
	"__initcall_etnaviv_init6",
	"__initcall_mxsfb_platform_driver_init6",
	"__initcall_cn_proc_init6",
	"__initcall_topology_sysfs_init6",
	"__initcall_cacheinfo_sysfs_init6",
	"__initcall_devcoredump_init6",
	"__initcall_loop_init6",
	"__initcall_init6",
	"__initcall_mtip_init6",
	"__initcall_at24_init6",
	"__initcall_at25_driver_init6",
	"__initcall_system_heap_create6",
	"__initcall_add_default_cma_heap6",
	"__initcall_init6",
	"__initcall_init_sd6",
	"__initcall_init_sg6",
	"__initcall_nvme_core_init6",
	"__initcall_nvme_init6",
	"__initcall_spidev_init6",
	"__initcall_spi_imx_driver_init6",
	"__initcall_ipvlan_init_module6",
	"__initcall_ipvtap_init6",
	"__initcall_mod_init6",
	"__initcall_macvlan_init_module6",
	"__initcall_macvtap_init6",
	"__initcall_net_olddevs_init6",
	"__initcall_blackhole_netdev_init6",
	"__initcall_phy_module_init6",
	"__initcall_fixed_mdio_bus_init6",
	"__initcall_mdio_mux_multiplexer_driver_init6",
	"__initcall_tun_init6",
	"__initcall_veth_init6",
	"__initcall_virtio_net_driver_init6",
	"__initcall_fec_driver_init6",
	"__initcall_ath5k_pci_driver_init6",
	"__initcall_ath9k_init6",
	"__initcall_ath9k_cmn_init6",
	"__initcall_ath9k_htc_init6",
	"__initcall_ar5523_driver_init6",
	"__initcall_ath10k_pci_init6",
	"__initcall_cdc_driver_init6",
	"__initcall_eem_driver_init6",
	"__initcall_usbnet_init6",
	"__initcall_ipheth_driver_init6",
	"__initcall_net_failover_init6",
	"__initcall_dwc3_driver_init6",
	"__initcall_mon_init6",
	"__initcall_ehci_hcd_init6",
	"__initcall_ehci_pci_init6",
	"__initcall_ohci_hcd_mod_init6",
	"__initcall_xhci_hcd_init6",
	"__initcall_xhci_pci_init6",
	"__initcall_xhci_plat_init6",
	"__initcall_fsl_usb2_mph_dr_driver_init6",
	"__initcall_ehci_fsl_init6",
	"__initcall_acm_init6",
	"__initcall_usblp_driver_init6",
	"__initcall_wdm_driver_init6",
	"__initcall_usbtmc_driver_init6",
	"__initcall_uas_init6",
	"__initcall_usb_storage_driver_init6",
	"__initcall_usb_serial_init6",
	"__initcall_usb_serial_module_init6",
	"__initcall_usb_serial_module_init6",
	"__initcall_usb_serial_module_init6",
	"__initcall_input_leds_init6",
	"__initcall_mousedev_init6",
	"__initcall_joydev_init6",
	"__initcall_evdev_init6",
	"__initcall_imx_snvs_pwrkey_driver_init6",
	"__initcall_xpad_driver_init6",
	"__initcall_pcf8523_driver_init6",
	"__initcall_snvs_rtc_driver_init6",
	"__initcall_i2c_dev_init6",
	"__initcall_lpi2c_imx_driver_init6",
	"__initcall_pca954x_driver_init6",
	"__initcall_i2c_mux_pinctrl_driver_init6",
	"__initcall_i2c_mux_reg_driver_init6",
	"__initcall_uvc_init6",
	"__initcall_gspca_init6",
	"__initcall_sd_driver_init6",
	"__initcall_syscon_reboot_driver_init6",
	"__initcall_syscon_poweroff_register6",
	"__initcall_pwm_fan_driver_init6",
	"__initcall_thermal_mmio_driver_init6",
	"__initcall_imx_thermal_init6",
	"__initcall_qoriq_tmu_init6",
	"__initcall_imx2_wdt_driver_init6",
	"__initcall_dm_init6",
	"__initcall_dm_bufio_init6",
	"__initcall_dm_bio_prison_init6",
	"__initcall_dm_crypt_init6",
	"__initcall_dm_thin_init6",
	"__initcall_bcm203x_driver_init6",
	"__initcall_btusb_driver_init6",
	"__initcall_ath3k_driver_init6",
	"__initcall_dt_cpufreq_platdrv_init6",
	"__initcall_imx_cpufreq_dt_driver_init6",
	"__initcall_arm_idle_init6",
	"__initcall_psci_idle_init6",
	"__initcall_mmc_pwrseq_simple_driver_init6",
	"__initcall_mmc_pwrseq_emmc_driver_init6",
	"__initcall_mmc_blk_init6",
	"__initcall_sdhci_drv_init6",
	"__initcall_sdhci_pltfm_drv_init6",
	"__initcall_sdhci_esdhc_imx_driver_init6",
	"__initcall_sdhci_esdhc_driver_init6",
	"__initcall_gpio_led_driver_init6",
	"__initcall_pca955x_driver_init6",
	"__initcall_dmi_sysfs_init6",
	"__initcall_esrt_sysfs_init6",
	"__initcall_efivars_pstore_init6",
	"__initcall_efibc_init6",
	"__initcall_smccc_soc_init6",
	"__initcall_caam_driver_init6",
	"__initcall_jr_driver_init6",
	"__initcall_virtio_crypto_driver_init6",
	"__initcall_hid_init6",
	"__initcall_uhid_misc_init6",
	"__initcall_hid_generic_init6",
	"__initcall_lg_driver_init6",
	"__initcall_lg_g15_driver_init6",
	"__initcall_logi_djreceiver_driver_init6",
	"__initcall_hidpp_driver_init6",
	"__initcall_magicmouse_driver_init6",
	"__initcall_ms_driver_init6",
	"__initcall_sony_init6",
	"__initcall_wacom_driver_init6",
	"__initcall_wiimote_hid_driver_init6",
	"__initcall_hid_init6",
	"__initcall_bcma_modinit6",
	"__initcall_hantro_driver_init6",
	"__initcall_ashmem_init6",
	"__initcall_imx_mu_driver_init6",
	"__initcall_imx_ddr_pmu_driver_init6",
	"__initcall_binder_init6",
	"__initcall_imx_ocotp_driver_init6",
	"__initcall_mux_gpio_driver_init6",
	"__initcall_mux_mmio_driver_init6",
	"__initcall_icc_init6",
	"__initcall_imx8mq_icc_driver_init6",
	"__initcall_alsa_hwdep_init6",
	"__initcall_alsa_timer_init6",
	"__initcall_snd_hrtimer_init6",
	"__initcall_alsa_pcm_init6",
	"__initcall_alsa_rawmidi_init6",
	"__initcall_alsa_mixer_oss_init6",
	"__initcall_alsa_pcm_oss_init6",
	"__initcall_alsa_seq_init6",
	"__initcall_seq_midisynth_driver_init6",
	"__initcall_usb_audio_driver_init6",
	"__initcall_snd_soc_init6",
	"__initcall_ac97_codec_driver_init6",
	"__initcall_hdmi_codec_driver_init6",
	"__initcall_wm8960_i2c_driver_init6",
	"__initcall_asoc_simple_card_init6",
	"__initcall_graph_card_init6",
	"__initcall_fsl_audmix_driver_init6",
	"__initcall_fsl_asoc_card_driver_init6",
	"__initcall_fsl_asrc_driver_init6",
	"__initcall_fsl_sai_driver_init6",
	"__initcall_fsl_ssi_driver_init6",
	"__initcall_fsl_spdif_driver_init6",
	"__initcall_fsl_esai_driver_init6",
	"__initcall_fsl_micfil_driver_init6",
	"__initcall_fsl_aud2htx_driver_init6",
	"__initcall_imx_spdif_driver_init6",
	"__initcall_imx_audmix_driver_init6",
	"__initcall_imx_hdmi_driver_init6",
	"__initcall_sock_diag_init6",
	"__initcall_failover_init6",
	"__initcall_llc_init6",
	"__initcall_snap_init6",
	"__initcall_netlink_diag_init6",
	"__initcall_nfnetlink_init6",
	"__initcall_nfnl_acct_init6",
	"__initcall_nfnetlink_queue_init6",
	"__initcall_nfnetlink_log_init6",
	"__initcall_nf_conntrack_standalone_init6",
	"__initcall_nf_nat_init6",
	"__initcall_nf_conncount_modinit6",
	"__initcall_nf_tables_module_init6",
	"__initcall_nft_compat_module_init6",
	"__initcall_nft_connlimit_module_init6",
	"__initcall_nft_ct_module_init6",
	"__initcall_nft_limit_module_init6",
	"__initcall_nft_nat_module_init6",
	"__initcall_nft_queue_module_init6",
	"__initcall_nft_quota_module_init6",
	"__initcall_nft_reject_inet_module_init6",
	"__initcall_nft_tunnel_module_init6",
	"__initcall_nft_counter_module_init6",
	"__initcall_nft_log_module_init6",
	"__initcall_nft_masq_module_init6",
	"__initcall_nft_redir_module_init6",
	"__initcall_nft_socket_module_init6",
	"__initcall_nft_tproxy_module_init6",
	"__initcall_nft_chain_nat_init6",
	"__initcall_nft_dup_netdev_module_init6",
	"__initcall_nft_fwd_netdev_module_init6",
	"__initcall_xt_init6",
	"__initcall_tcpudp_mt_init6",
	"__initcall_mark_mt_init6",
	"__initcall_xt_nat_init6",
	"__initcall_checksum_tg_init6",
	"__initcall_redirect_tg_init6",
	"__initcall_masquerade_tg_init6",
	"__initcall_addrtype_mt_init6",
	"__initcall_comment_mt_init6",
	"__initcall_conntrack_mt_init6",
	"__initcall_gre_offload_init6",
	"__initcall_sysctl_ipv4_init6",
	"__initcall_esp4_init6",
	"__initcall_tunnel4_init6",
	"__initcall_nf_defrag_init6",
	"__initcall_nft_reject_ipv4_module_init6",
	"__initcall_nft_dup_ipv4_module_init6",
	"__initcall_ip_tables_init6",
	"__initcall_iptable_filter_init6",
	"__initcall_iptable_mangle_init6",
	"__initcall_iptable_nat_init6",
	"__initcall_cubictcp_register6",
	"__initcall_xfrm_user_init6",
	"__initcall_unix_diag_init6",
	"__initcall_inet6_init6",
	"__initcall_ah6_init6",
	"__initcall_esp6_init6",
	"__initcall_ipcomp6_init6",
	"__initcall_xfrm6_tunnel_init6",
	"__initcall_tunnel6_init6",
	"__initcall_ip6_tables_init6",
	"__initcall_ip6table_mangle_init6",
	"__initcall_ip6table_nat_init6",
	"__initcall_nf_defrag_init6",
	"__initcall_nft_reject_ipv6_module_init6",
	"__initcall_sit_init6",
	"__initcall_packet_init6",
	"__initcall_packet_diag_init6",
	"__initcall_ipsec_pfkey_init6",
	"__initcall_br_init6",
	"__initcall_br_netfilter_init6",
	"__initcall_rfcomm_init6",
	"__initcall_bnep_init6",
	"__initcall_hidp_init6",
	"__initcall_rfkill_gpio_driver_init6",
	"__initcall_init_dns_resolver6",
	"__initcall_xen_pm_init7",
	"__initcall_init_oops_id7",
	"__initcall_reboot_ksysfs_init7",
	"__initcall_sched_init_debug7",
	"__initcall_cpu_latency_qos_init7",
	"__initcall_pm_debugfs_init7",
	"__initcall_printk_late_init7",
	"__initcall_init_srcu_module_notifier7",
	"__initcall_swiotlb_create_debugfs7",
	"__initcall_tk_debug_sleep_time_init7",
	"__initcall_debugfs_kprobe_init7",
	"__initcall_taskstats_init7",
	"__initcall_kdb_ftrace_register7",
	"__initcall_bpf_map_iter_init7",
	"__initcall_task_iter_init7",
	"__initcall_bpf_prog_iter_init7",
	"__initcall_init_trampolines7",
	"__initcall_load_system_certificate_list7",
	"__initcall_fault_around_debugfs7",
	"__initcall_max_swapfiles_check7",
	"__initcall_init_zswap7",
	"__initcall_split_huge_pages_debugfs7",
	"__initcall_check_early_ioremap_leak7",
	"__initcall_set_hardened_usercopy7",
	"__initcall_pstore_init7",
	"__initcall_init_root_keyring7",
	"__initcall_init_profile_hash7",
	"__initcall_integrity_fs_init7",
	"__initcall_blk_timeout_init7",
	"__initcall_prandom_init_late7",
	"__initcall_init_error_injection7",
	"__initcall_pci_resource_alignment_sysfs_init7",
	"__initcall_pci_sysfs_init7",
	"__initcall_amba_deferred_retry7",
	"__initcall_clk_debug_init7",
	"__initcall_setup_vcpu_hotplug_event7",
	"__initcall_sync_state_resume_initcall7",
	"__initcall_deferred_probe_initcall7",
	"__initcall_genpd_power_off_unused7",
	"__initcall_genpd_debug_init7",
	"__initcall_vxlan_init_module7",
	"__initcall_firmware_memmap_init7",
	"__initcall_register_update_efi_random_seed7",
	"__initcall_efi_shutdown_init7",
	"__initcall_efi_earlycon_unmap_fb7",
	"__initcall_of_fdt_raw_init7",
	"__initcall_bpf_sk_storage_map_iter_init7",
	"__initcall_tcp_congestion_default7",
	"__initcall_udp_tunnel_nic_init_module7",
	"__initcall_regulatory_init_db7",
	"__initcall_init_amu_fie7s",
	"__initcall_software_resume7s",
	"__initcall_latency_fsnotify_init7s",
	"__initcall_trace_eval_sync7s",
	"__initcall_clear_boot_tracer7s",
	"__initcall_fb_logo_late_init7s",
	"__initcall_clk_disable_unused7s",
	"__initcall_imx_clk_disable_uart7s",
	"__initcall_regulator_init_complete7s",
	"__initcall_of_platform_sync_state_init7s",
	"__initcall_alsa_sound_last_init7s",
	"__initcall_con_init",
	"__initcall_end",
	"__initcall_hvc_console_init",
	"__initcall_kgdboc_earlycon_late_init",
	"END_OF_INITCALL_ORDER_ARRAY_DUMMY_ENTRY"
};

#endif /* _LX_EMUL__INITCALL_ORDER_H_ */
