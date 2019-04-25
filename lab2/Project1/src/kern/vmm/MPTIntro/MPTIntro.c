
#include <lib/gcc.h>
#include <lib/x86.h>
#include <lib/debug.h>

#include "import.h"

#define PT_PERM_UP 0
#define PT_PERM_PTU (PTE_P | PTE_W | PTE_U)





/** ASSIGNMENT INFO:
  * - In this part of the kernel, we will be implementing Virtual Memory Management (VMM) with
  *   two level paging mechanism.
  * - Like with PMM section, we need certain data structures and abstractions over these structures
  *   to access and modify them. (See project handout for description of abstraction layers.)
  * - Each abstraction layer is a sub-folder within the vmm folder and is organised the same as
  *   pmm layer with files export.h, import.h, test.c, <layer_name>.c and the Makefile.inc.
  *
  * HELPFUL LINKS ON PAGING:
  * - Intel 80386 Programmer’s Reference Manual: http://flint.cs.yale.edu/cs422/readings/i386/s05_02.htm
  */

/** * VMM Data Structure: PDirPool
  * - We will maintain one page structure for each process.
  * - We will statically allocate page directories, and maintain the second level page tables dynamically.
  * - We have a Page directory pool for NUM_IDS processes.
  *   -- Each PDirPool[index] represents the page directory of the page structure for the process # [index].
  * - We will have a maximum of NUM_IDS (=64) processes.
  * - The PAGESIZE for VMM is 4096 bytes.
  * - Each Page Table Entry (pte) is 4 bytes. Therefore, each page can hold 4096/4 = 1024 pte.
  * Page Table Entry Format:
  *
  * |31                         12|11          |2   |1   |0  |
  * |-----------------------------|------------|----|----|---|
  * | Page Frame Address 31..12   |  Flags     |U/S |R/W |P  |
  *
  * - U/S = User / Supervisor bit
  * - R/W = Read / Write bit
  * - P   = Present bit
  */
char * PDirPool[NUM_IDS][1024] gcc_aligned(PAGESIZE);

/** * VMM Data Structure: IDPTbl
  * - In mCertiKOS, we use identity page table mappings for the kernel memory.
  * - IDPTbl is a statically allocated, identity page table that will be reused for
  *   all the kernel memory.
  * - Every page directory entry of kernel memory links to corresponding entry in IDPTbl.
  */
unsigned int IDPTbl[1024][1024] gcc_aligned(PAGESIZE);


/** TASK 1:
  * * Set the CR3 register with the start address of the page structure for process # [index]
  */
void set_pdir_base(unsigned int index)
{
    // TODO

	set_cr3(PDirPool[index]);

}

/** TASK 2:
  * * Return the page directory entry # [pde_index] of the process # [proc_index]
  * - This can be used to test whether the page directory entry is mapped
  */
unsigned int get_pdir_entry(unsigned int proc_index, unsigned int pde_index)
{
    // TODO
	return (unsigned int)PDirPool[proc_index][pde_index];


}

/** TASK 3:
  * * Set specified page directory entry with the start address of physical page # [page_index].
  * - You should also set the permissions PTE_P, PTE_W, and PTE_U
  * Hint 1: PT_PERM_PTU is defined for you.
  * Hint 2:
  */
void set_pdir_entry(unsigned int proc_index, unsigned int pde_index, unsigned int page_index)
{
    // TODO
   // bit 31-12 is the base address of page table
    unsigned int value = (page_index << 12) | PT_PERM_PTU; 
    PDirPool[proc_index][pde_index] = (char *)value;



}

/** TASK 4:
  * * Set the page directory entry # [pde_index] for the process # [proc_index]
  *   with the initial address of page directory # [pde_index] in IDPTbl
  * - You should also set the permissions PTE_P, PTE_W, and PTE_U
  * - This will be used to map the page directory entry to identity page table.
  * Hint 1: Cast the first entry of IDPTbl[pde_index] to char *.
  */
void set_pdir_entry_identity(unsigned int proc_index, unsigned int pde_index)
{
    // TODO

// the address of IDPTbl[pde_index] is aligned to 4096
    // so the low 12bits are all 0
    unsigned int value = (unsigned int)IDPTbl[pde_index];
    value |= PT_PERM_PTU;
    PDirPool[proc_index][pde_index] = (char *)value;

}

/** TASK 5:
  * * Remove specified page directory entry
  * Hint 1: Set the page directory entry to PT_PERM_UP.
  * Hint 2: Don't forget to cast the value to (char *).
  */
void rmv_pdir_entry(unsigned int proc_index, unsigned int pde_index)
{
    // TODO

	PDirPool[proc_index][pde_index] = (char *)0x00000000;

}

/** TASK 6:
  * * Returns the specified page table entry.
  * Hint 1: Remember that second level page table is dynamically allocated. You cannot simply
  *         use array indexing as in the first level page table. The offset into the second level
  *         page table can be calculated using: pte_index * size of pte.
  * Hint 2: Do not forget that the permission info is also stored in the page directory entries.
  *         (You will have to mask out the permission info.)
  * Hint 3: Remember to cast to a pointer before de-referencing an address.
  */
unsigned int get_ptbl_entry(unsigned int proc_index, unsigned int pde_index, unsigned int pte_index)
{
    // TODO
    // PdirPool[proc_index][pde_index] stores the bass address of a page table
    // pte_index * 4 means each page table entry is 4 byte.
    unsigned int pte_addr = (unsigned int )PDirPool[proc_index][pde_index];
    pte_addr &= 0xfffff000; //remove perm bits
    pte_addr += pte_index << 2;//

    return *(unsigned int *)pte_addr; 

}

/** TASK 7:
  * * Sets specified page table entry with the start address of physical page # [page_index]
  * - You should also set the given permission
  * Hint 1: Same as TASK 6
  */
void set_ptbl_entry(unsigned int proc_index, unsigned int pde_index, unsigned int pte_index, unsigned int page_index, unsigned int perm)
{
    // TODO
// each page table entry is 4 byte, char * is also 4 byte
    unsigned int* pte;
    unsigned int pte_addr =  (unsigned int )PDirPool[proc_index][pde_index];
    pte_addr &= 0xfffff000;//rmove perm bits
    pte_addr += pte_index << 2;

    pte = (unsigned int *)pte_addr;
    *pte &= 0x00000000;
    *pte = page_index << 12;
    *pte |= (perm & 0x00000fff);


}

/** TASK 8:
  * * Set the specified page table entry in IDPTbl as the identity map.
  * - You should also set the given permission
  * Hint 1: Remember that c-language is row-major i.e. for a multi-dimensional array,
  *         the consecutive elements of a row reside next to each other.
  * eg. a 2-dimensional array: A[2][3] is stored in memory as follows.
  *  [https://en.wikipedia.org/wiki/Row-_and_column-major_order]
  * | Address | Array access |
  * |---------|--------------|
  * | 0       |    A[0][0]   |
  * | 1       |    A[0][1]   |       address for A[i][j] is calculated as:
  * | 2       |    A[0][2]   |       addr = (i * num_columns + j) * size_of_each_entry
  * | 3       |    A[1][0]   |       eg. A[1][2] -> (1 * 3 + 2) * 1 = 5
  * | 4       |    A[1][1]   |
  * | 5       |    A[1][2]   |
  * |---------|--------------|
  */
void set_ptbl_entry_identity(unsigned int pde_index, unsigned int pte_index, unsigned int perm)
{
    // TODO
    IDPTbl[pde_index][pte_index] = ((pde_index << 10) + pte_index) << 12;
    IDPTbl[pde_index][pte_index] |= perm;


}

/** TASK 9:
  * * Set the specified page table entry to 0
  * Hint 1: Remember that page directory entries also have permissions stored. Mask them out.
  * Hint 2: Remember to cast to a pointer before de-referencing an address.
  */
void rmv_ptbl_entry(unsigned int proc_index, unsigned int pde_index, unsigned int pte_index)
{
    // TODO
    unsigned int * pte;
    unsigned int pte_addr = (unsigned int)PDirPool[proc_index][pde_index];
    pte_addr &= 0xfffff000;//remove perm bits
    pte_addr += pte_index << 2;
    pte = (unsigned int *)pte_addr;
    *pte &= 0x00000000;



}


/** TASK 1:
  * * Copy PTE entry assuming page directory exists
  *   - If original PTE entry is not zero, attach the PTE_COW permission at the end of both.
  *   - If original PTE entry is zero, set the new one to be zero as well
  */
void copy_ptbl_entry(uint32_t from_pid, uint32_t to_pid, uint32_t pde_index, uint32_t pte_index){
  // TODO






}


/** TASK 2:
  * * Copy page table corresponding to pde_index
  *   - If it doesn't exist in from_pid, set to_pid entry to 0
  */
void copy_pdir_entry(uint32_t from_pid, uint32_t to_pid, uint32_t pde_index){
  // TODO






}

/** Prints the entire page table. */
void print_table(uint32_t pid){
    uint32_t pde_index, pte_index;
    uint32_t pde_entry, pte_entry;
    KERN_DEBUG("page table %d\n", pid);
    for(pde_index = 256; pde_index < 960; pde_index++){
        pde_entry = get_pdir_entry(pid, pde_index);
        if (pde_entry == 0) continue;
        KERN_DEBUG("PDE %d: %p\n", pde_index, pde_entry & 0xfffff000);
        for(pte_index = 0; pte_index < 1024; pte_index++){
            pte_entry = get_ptbl_entry(pid, pde_index, pte_index);
            if (pte_entry == 0) continue;
            KERN_DEBUG("PDE %d PTE %d: %p\n", pde_index, pte_index, pte_entry);
        }
    }
}
