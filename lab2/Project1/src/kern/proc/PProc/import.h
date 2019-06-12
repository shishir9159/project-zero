#ifndef _KERN_PROC_PPROC_H_
#define _KERN_PROC_PPROC_H_

#ifdef _KERN_

unsigned int get_curid(void);
void set_pdir_base(unsigned int);
unsigned int thread_spawn(void *entry, unsigned int id, unsigned int quota);

// fork
uint32_t thread_fork(void *entry, uint32_t id);

#endif /* _KERN_ */

#endif /* !_KERN_PROC_PPROC_H_ */
