
#include <lib/x86.h>
#include <lib/thread.h>

#include "import.h"

void thread_init(unsigned int mbi_addr)
{
	tqueue_init(mbi_addr);
	set_curid(0);
	tcb_set_state(0, TSTATE_RUN);
}

/** TASK 1:
  * * Allocate new child thread context, set the state of the new child thread
  *   as ready, and push it to the ready queue.
  *   It returns the child thread id.
  *  Hint 1:
  *  - import.h has all the functions you will need.
  *  Hint 2:
  *  - The ready queue is the queue with index NUM_IDS.
  */
unsigned int thread_spawn(void *entry, unsigned int id, unsigned int quota)
{
  // TODO

int child = kctx_new(entry, id, quota);
  tcb_set_state(child, TSTATE_READY);
  tqueue_enqueue(NUM_IDS, child);
return child;





  //return 0;
}

/** TASK 2:
  * * Yield to the next thread in the ready queue. You should:
  *   - Set the currently running thread state as ready,
  *     and push it back to the ready queue.
  *   - Set the state of the poped thread as running
  *   - Set the current thread id
  *   - Then switch to the new kernel context.
  *
  *  Hint 1: The next thread to run is chosen in a round-robin fashion.
  *          i.e. The thread at the head of the ready queue is run next.
  *  Hint 2: If you are the only thread that is ready to run,
  *          do you need to switch to yourself?
  */
void thread_yield(void)
{
  // TODO

int curid = get_curid();
  int next_ready = tqueue_dequeue(NUM_IDS);
  if (next_ready == NUM_IDS) {
    //no ready threads then return
    return;
  }
  //set current running thread's state to ready
  tcb_set_state(curid, TSTATE_READY);
  //push the current thread to ready queue
  tqueue_enqueue(NUM_IDS, curid);
  
  //set the state of next ready thread
  tcb_set_state(next_ready, TSTATE_RUN);
  
  //set current thread id, switch context
  set_curid(next_ready);
kctx_switch(curid, next_ready); 





}


/** TASK 1:
  * * Allocate the forked child thread context, map page structures for the child,
  *   set the state of the new child thread as ready, and push it to the ready queue.
  *   It returns the child thread id.
  *  Hint 1:
  *  - import.h has all the functions you will need.
  *  Hint 2:
  *  - The ready queue is the queue with index NUM_IDS.
  */

uint32_t thread_fork(void *entry, uint32_t id){
    // TODO

//allocating the forked child thread context
  uint32_t child = kctx_fork(entry , id);
  
  //mapping page structure for the child
  map_cow(id , child);

  unsigned int child_unsigned = (unsigned int) child;
  //setting the state of the new child thread as ready
  tcb_set_state(child_unsigned , TSTATE_READY);

  //pushing the new child thread into the ready queue
  tqueue_enqueue(NUM_IDS , child_unsigned);

  return child;





}