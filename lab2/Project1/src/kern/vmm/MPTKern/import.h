#ifndef _KERN_MM_MPTKERN_H_
#define _KERN_MM_MPTKERN_H_

#ifdef _KERN_

void pdir_init(unsigned int); //used
void set_pdir_entry_identity(unsigned int, unsigned int); //used
unsigned int get_pdir_entry_by_va(unsigned int, unsigned int); //used
unsigned int alloc_ptbl(unsigned int, unsigned int); //used
void set_ptbl_entry_by_va(unsigned int, unsigned int, unsigned int, unsigned int); //used
void rmv_ptbl_entry_by_va(unsigned int, unsigned int); //used
unsigned int get_ptbl_entry_by_va(unsigned int, unsigned int); //used

#endif /* _KERN_ */

#endif /* !_KERN_MM_MPTKERN_H_ */
