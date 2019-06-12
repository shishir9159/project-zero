#ifndef _KERN_TRAP_TTRAPHANDLER_H_
#define _KERN_TRAP_TTRAPHANDLER_H_

#ifdef _KERN_

unsigned int syscall_get_arg1(void);
void set_pdir_base(unsigned int); //used
void proc_start_user(void); //used
void print_kctx(uint32_t pid);
void map_decow(uint32_t pid, uint32_t vadr); //used

#endif /* _KERN_ */

#endif /* !_KERN_TRAP_TTRAPHANDLER_H_ */
