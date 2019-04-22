#ifndef _KERN_MM_MPTINTRO_H_
#define _KERN_MM_MPTINTRO_H_

#ifdef _KERN_

void set_cr3(char **); // sets the CR3 register

unsigned int container_alloc(unsigned int); // imported from pmm/Mcontainer
unsigned int alloc_page (unsigned int , unsigned int , unsigned int );

#endif /* _KERN_ */

#endif /* !_KERN_MM_MPTINTRO_H_ */
