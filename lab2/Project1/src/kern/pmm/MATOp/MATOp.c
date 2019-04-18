#include <lib/debug.h>
#include "import.h"

#define PAGESIZE  4096
#define VM_USERLO 0x40000000
#define VM_USERHI 0xF0000000
#define VM_USERLO_PI  (VM_USERLO / PAGESIZE)   // VM_USERLO page index
#define VM_USERHI_PI  (VM_USERHI / PAGESIZE)   // VM_USERHI page index

//set a next pointer to remember the last allocated page index
static unsigned int next = VM_USERLO_PI;

/** TASK 1:
  * Allocation of a physical page.
  *
  * 1. - First, implement a naive page allocator that scans the allocation table (AT)
  *      using the functions defined in import.h to find the first unallocated page
  *      with usable permission.
  *
  *    Hint 1: (Q: Do you have to scan allocation table from index 0? Recall how you have
  *    			initialized the table in pmem_init.)
  *
  *    - Then mark the page as allocated in the allocation table and return the page
  *    	 index of the page found. In the case when there is no available page found,
  *      return 0.
  * 2. Optimize the code with the memorization techniques so that you do not have to
  *    scan the allocation table from scratch every time.
  */
unsigned int palloc()
{
  // TODO



 // // 1. naive page allocator approach
  //no available physical pages
  if (get_nps() == 0) {
    return 0;
  }

  //first record the current value of next
  unsigned int begin = next;
  do {
    //if the page pointed by next has the usable permission and it's not allocated
    //then allocate the page, and return the page index
    if (at_is_norm(next) && at_is_allocated(next) == 0) {
      at_set_allocated(next, 1);
      return next;
    }
    next++;
    //if next moves to the end, we set next to the beginning
    if (next == VM_USERHI_PI) {
      next = VM_USERLO_PI;
    }
  } while (next != begin);

//all pages are allocated



// 2. optimization with the memorization techniques
// usable permission only lies within user space of physical memory. so checking only needs within user space.



  return 0; // if no available page is found

}


/** TASK 2:
  * Free of a physical page.
  *
  * This function marks the page with given index as unallocated in the allocation table.
  *
  * Hint: Simple. You have already implemented the functions required to check if a page
  * 	  is allocated and to set the allocation status of a page index. (See import.h)
  */
void
pfree(unsigned int pfree_index)
{
  // TODO

	at_set_allocated(pfree_index, 0);




}
