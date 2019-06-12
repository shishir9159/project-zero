/*
 * void cswitch(struct kctx *from, struct kctx *to);
 */

	.globl cswitch
cswitch:
	/**
	  * The pointer *from is saved to register %eax.
	  * This is the pointer to the kctx structure to be saved.
	  */
	movl	  4(%esp), %eax	

	/**
	  * The pointer *to is saved to register %edx.
	  * This is the pointer to the kctx structure to be loaded.
	  */
	movl	  8(%esp), %edx	

	/** TASK 1:
	  *  * Save the old kernel context 
	  *  Hint 1: 
	    struct kctx {
			void	*esp;
			unsigned int edi;
			unsigned int esi;
			unsigned int ebx;
			unsigned int ebp;
			void	*eip;
		};

		- %eax holds the pointer to this kctx structure. Each field in this structure is 4bytes.
		  So, Memory location 0(%eax) holds the value of the first field of this structure (i.e. esp)
		      Memory location 4(%eax) holds the value of the second field of this structure (i.e. edi)
		      and so on ...
		- To save the old kernel context, you have to save the values of the corresponding registers 
		  into these memory locations.

	  *  Hint 2:
	  *  - Remember that eip in kctx structure should hold the return address pushed onto the current thread's stack (i.e. 0(%esp))
	  */
      
      movl %esp, 0(%eax)

      movl %edi, 4(%eax)	
      movl %esi, 8(%eax)
      movl %ebx, 12(%eax)
      movl %ebp, 16(%eax)

      xorl %ebx, %ebx  
      movl 0(%esp), %ebx
      movl %ebx, 20(%eax)
      xorl %ebx, %ebx 



	/** TASK 2:
	  *  * Load the new kernel context
	  *  Hint 1:
	  *  - Here you need to LOAD the values from the kctx structure of the new kernel context into the corresponding registers.
	  *  
	  *  Hint 2: 
	  *  - %eip is not a general purpose register and cannot be manipulated directly. Instead we load the eip from kctx structure 
	  *    to as the return address. For this, we want to place the eip field of kctx structure onto the top of the stack (i.e. 0(%esp))
	  *    so that it will use that value in the ret statement.  
	  */

      movl 0(%edx), %esp

      movl 4(%edx), %edi	
      movl 8(%edx), %esi
      movl 12(%edx), %ebx
      movl 16(%edx), %ebp

      xorl %ebx, %ebx
      movl 20(%edx), %ebx
      movl %ebx, 0(%esp)
      xorl %ebx, %ebx



	/**
	  * The return value is stored in eax. Returns 0.
	  */
	xor     %eax, %eax
	ret
