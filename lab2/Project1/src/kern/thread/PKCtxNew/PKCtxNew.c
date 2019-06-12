
#include <lib/gcc.h>
#include <lib/x86.h>

#include "import.h"

extern char STACK_LOC[NUM_IDS][PAGESIZE] gcc_aligned(PAGESIZE);

/** TASK 1:
  * * Allocate memory for the new child thread, then set the eip, and esp
  *   of the thread states. The eip should be set to [entry], and the
  *   esp should be set to the corresponding stack TOP in STACK_LOC.
  *   Don't forget the stack is going down from high address to low.
  *   We do not care about the rest of states when a new thread starts.
  *   The function returns the child thread (process) id.
  *
  *  Hint 1:
  *  - The alloc_mem_quota function will return the pid of the child process.
  *    Use this to set the eip and esp in the context using functions defined in import.h.
  *  Hint 2:
  *  - Set eip to [entry]
  *  - Set esp to corresponding stack TOP in STACK_LOC.
  *    i.e. Address of STACK_LOC[child][PAGESIZE - 1]. Remember that the stack is going down from high address to low.
  *  Hint 3:
  *  - Return the child pid.
  */
unsigned int kctx_new(void *entry, unsigned int id, unsigned int quota)
{
  // TODO
  unsigned int child = alloc_mem_quota(id, quota);
  kctx_set_eip(child, entry);
  kctx_set_esp(child, (void *)&STACK_LOC[child][PAGESIZE-1]);
  
return child;






  //return 0;
}

/** TASK 1:
  * * Allocate half of the AVAILABLE memory for the newly forked child thread, then set the eip, and esp
  *   of the thread states. The eip should be set to [entry], and the
  *   esp should be set to the corresponding stack TOP in STACK_LOC.
  *   Don't forget the stack is going down from high address to low.
  *   We do not care about the rest of states when a new thread starts.
  *   The function returns the child thread (process) id.
  *
  *  Hint 1:
  *  - quota for the forked child theard should be half of the AVAILBLE memory
  *  Hint 2:
  *  - The alloc_mem_quota function will return the pid of the child process.
  *    Use this to set the eip and esp in the context using functions defined in import.h.
  *  Hint 3:
  *  - Set eip to [entry]
  *  - Set esp to corresponding stack TOP in STACK_LOC.
  *    i.e. Address of STACK_LOC[child][PAGESIZE - 1]. Remember that the stack is going down from high address to low.
  *  Hint 3:
  *  - Return the child pid.
  */
unsigned int kctx_fork(void *entry, uint32_t id){
  // TODO
unsigned int quota = container_get_quota(id);
  unsigned int child_index = alloc_mem_quota(id , quota);

  kctx_set_eip(child_index , entry);
  kctx_set_esp(child_index , STACK_LOC[child_index][PAGESIZE - 1]);




  return child_index;







  //return 0;
}

