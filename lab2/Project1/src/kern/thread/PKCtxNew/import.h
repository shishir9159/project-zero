#ifndef _KERN_THREAD_PKCTXNEW_H_
#define _KERN_THREAD_PKCTXNEW_H_

#ifdef _KERN_

unsigned int alloc_mem_quota(unsigned int id, unsigned int quota);
void kctx_set_esp(unsigned int pid, void *esp);
void kctx_set_eip(unsigned int pid, void *eip);

// fork
unsigned int container_get_quota(unsigned int id);
unsigned int container_get_usage(unsigned int id);
void *kctx_get_esp(uint32_t pid); // not used
void *kctx_get_eip(uint32_t pid); // not used

#endif /* _KERN_ */

#endif /* !_KERN_THREAD_PKCTXNEW_H_ */