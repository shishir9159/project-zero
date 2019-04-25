#ifndef _KERN_MM_MPTOP_H_
#define _KERN_MM_MPTOP_H_

#ifdef _KERN_

unsigned int container_alloc(unsigned int); //used
void container_free(unsigned int, unsigned int); //used
void idptbl_init(unsigned int); //used
void set_pdir_entry_identity(unsigned int, unsigned int); //used
void rmv_pdir_entry(unsigned int, unsigned int); //used
void rmv_ptbl_entry(unsigned int, unsigned int, unsigned int);
unsigned int get_pdir_entry_by_va(unsigned int, unsigned int); //used
void rmv_pdir_entry_by_va(unsigned int, unsigned int); //used
void set_pdir_entry_by_va(unsigned int, unsigned int, unsigned int); //used

#endif /* _KERN_ */

#endif /* !_KERN_MM_MPTOP_H_ */
