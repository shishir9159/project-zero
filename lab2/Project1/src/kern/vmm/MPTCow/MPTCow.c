
#include <lib/x86.h>
#include "import.h"


#define DIR_MASK    0xffc00000
#define PAGE_MASK   0x003ff000
#define OFFSET_MASK 0x00000fff
#define DIR_SHIFT   22
#define PAGE_SHIFT  12
#define PAGESIZE  4096
#define VM_USERLO 0x40000000
#define VM_USERHI 0xF0000000
#define VM_USERLO_PI  (VM_USERLO / PAGESIZE)   // VM_USERLO page index
#define VM_USERHI_PI  (VM_USERHI / PAGESIZE)   // VM_USERHI page index
#define PERM_USER (PTE_P | PTE_W)
#define PERM_KERNEL (PTE_P | PTE_W | PTE_G)
#define PT_PERM_PTU (PTE_P | PTE_W | PTE_U)
#define PERMISSION_OUT_MASK 0xFFFFF000



void map_cow (uint32_t from_pid, uint32_t to_pid)
{
  //dprintf("hello from map_cow from_pid: %d to_pid: %d\n", from_pid, to_pid);

  unsigned int low = (VM_USERLO & DIR_MASK) >> DIR_SHIFT;
  unsigned int high = (VM_USERHI & DIR_MASK) >> DIR_SHIFT;

  for (int i = low ; i < high; i++)
  {
    copy_pdir_entry(from_pid, to_pid, i);
  }

  //print_table(from_pid);
  //print_table(to_pid);
}


void map_decow (uint32_t pid, uint32_t vadr)
{
  //dprintf("hello from map_decow pid: %d vadr: %u\n ", pid, vadr);

  unsigned int virtual_address_dir = vadr & DIR_MASK;
  unsigned int pde_index = virtual_address_dir >> DIR_SHIFT;

  unsigned int virtual_address_page = vadr & PAGE_MASK;
  unsigned int pte_index = virtual_address_page >> PAGE_SHIFT;

  unsigned int ptbl_entry = get_ptbl_entry(pid, pde_index, pte_index);
  ptbl_entry = ptbl_entry & PERMISSION_OUT_MASK;

  unsigned int * temp_address = (unsigned int *) ptbl_entry;

  unsigned int new_page = alloc_page (pid, vadr, PT_PERM_PTU);
  unsigned int * temp_new_address = (unsigned int *) (new_page * PAGESIZE);

  for (int i = 0; i < 1024; i++)
  {
     temp_new_address[i] = temp_address[i];
  }

}