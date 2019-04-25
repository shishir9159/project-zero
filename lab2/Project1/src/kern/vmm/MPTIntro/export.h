#ifndef _KERN_MM_MPTINTRO_H_
#define _KERN_MM_MPTINTRO_H_

void set_pdir_base(unsigned int);
unsigned int get_pdir_entry(unsigned int, unsigned int);
void set_pdir_entry(unsigned int, unsigned int, unsigned int);
void set_pdir_entry_identity(unsigned int, unsigned int);
void rmv_pdir_entry(unsigned int, unsigned int);
unsigned int get_ptbl_entry(unsigned int, unsigned int, unsigned int);
void set_ptbl_entry(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
void set_ptbl_entry_identity(unsigned int, unsigned int, unsigned int);
void rmv_ptbl_entry(unsigned int, unsigned int, unsigned int);

void copy_ptbl_entry(uint32_t, uint32_t, uint32_t, uint32_t);
void copy_pdir_entry(uint32_t, uint32_t, uint32_t );
void print_table(uint32_t);

#endif

