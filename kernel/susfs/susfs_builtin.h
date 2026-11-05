/* SPDX-License-Identifier: GPL-2.0 */
/*
 * susfs_builtin.h - Graphite: compile KernelSU-Next's SuSFS into the kernel image instead of
 * loading it as a module (the husky kernel forces module signing and randomises struct layout,
 * so an externally built susfs_guard_lkm.ko cannot load).
 *
 * SuSFS keeps its own copies of the shared infra (symbol_resolver, lsm_hook, patch_memory) whose
 * APIs differ from the KSU driver's, so built into the same vmlinux their global names would
 * clash with the driver's. This header renames SuSFS's copies; it is force-included (-include)
 * into every SuSFS translation unit only, so the driver keeps the original names.
 *
 * Keep this list in step with the duplicate symbols reported by the linker: every name defined in
 * both susfs/{symbol_resolver,lsm_hook,patch_memory}.c and the KSU driver belongs here.
 */
#ifndef __SUSFS_BUILTIN_H
#define __SUSFS_BUILTIN_H

/* symbol_resolver.c */
#define find_kernel_symbol_exact		susfs_i_find_kernel_symbol_exact
#define ksu_init_symbol_resolver		susfs_i_ksu_init_symbol_resolver
#define ksu_resolve_symbol_for_functable_hook	susfs_i_ksu_resolve_symbol_for_functable_hook

/* lsm_hook.c */
#define ksu_lsm_hook				susfs_i_ksu_lsm_hook
#define ksu_lsm_hook_exit			susfs_i_ksu_lsm_hook_exit
#define ksu_lsm_hook_init			susfs_i_ksu_lsm_hook_init
#define ksu_lsm_unhook				susfs_i_ksu_lsm_unhook
#define ksu_register_lsm_hook			susfs_i_ksu_register_lsm_hook
#define ksu_unregister_lsm_hook			susfs_i_ksu_unregister_lsm_hook

/* patch_memory.c */
#define ksu_patch_text				susfs_i_ksu_patch_text
#define phys_from_virt				susfs_i_phys_from_virt
#define scan_call_to				susfs_i_scan_call_to

#endif /* __SUSFS_BUILTIN_H */
