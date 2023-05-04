#include <lib/elf.h>
#include <lib/debug.h>
#include <lib/gcc.h>
#include <lib/seg.h>
#include <lib/trap.h>
#include <lib/x86.h>
#include <lib/syscall.h>

#include "import.h"

extern tf_t uctx_pool[NUM_IDS];
extern char STACK_LOC[NUM_IDS][PAGESIZE];

void proc_start_user(void)
{
	unsigned int cur_pid = get_curid();
	tss_switch(cur_pid);
	set_pdir_base(cur_pid);

	trap_return((void *) &uctx_pool[cur_pid]);
}

unsigned int proc_create(void *elf_addr, unsigned int quota)
{
  unsigned int pid, id;

  id = get_curid();
  pid = thread_spawn((void *) proc_start_user, id, quota);

  elf_load(elf_addr, pid);

  uctx_pool[pid].es = CPU_GDT_UDATA | 3;
  uctx_pool[pid].ds = CPU_GDT_UDATA | 3;
  uctx_pool[pid].cs = CPU_GDT_UCODE | 3;
  uctx_pool[pid].ss = CPU_GDT_UDATA | 3;
  uctx_pool[pid].esp = VM_USERHI;
  uctx_pool[pid].eflags = FL_IF;
  uctx_pool[pid].eip = elf_entry(elf_addr);

  return pid;
}


/** TASK 1:
  * * Fork a new process.
  *     1. Similar to proc_create, fork a new thread using thread_fork() function (instead of thread_spawn.)
  *     2. Set the user context (uctx_pool) for the child thread.
  *  Hint: - Remember that fork duplicates the current process and
  *          the only difference is that the child process returns 0.
  *     3. This function should return the child_pid (the return value of thread_fork)
  */

uint32_t proc_fork(){
	// TODO








	//return 0;
}
