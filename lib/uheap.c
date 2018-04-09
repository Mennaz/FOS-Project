
#include <inc/lib.h>

// malloc()
//	This function use FIRST FIT strategy to allocate space in heap
//  with the given size and return void pointer to the start of the allocated space

//	To do this, we need to switch to the kernel, allocate the required space
//	in Page File then switch back to the user again.
//
//	We can use sys_allocateMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls allocateMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the allocateMem function is empty, make sure to implement it.


//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//

 struct Info {
 	uint32 add;
 	uint32 Size;
 	int Flag1;
 	int FirstIndex;
 };

 struct Info Visited[(KERNEL_HEAP_MAX-KERNEL_HEAP_START)/PAGE_SIZE];
 struct Info Spaces [(KERNEL_HEAP_MAX-KERNEL_HEAP_START)/PAGE_SIZE];
 uint32 Size_Of_Spaces=0;
 uint32 LastIndex=0;

void* malloc(uint32 size)
{
	uint32* First_add_allocated ;
	uint32 Req_Pages=(ROUNDUP(size,PAGE_SIZE)/PAGE_SIZE);    //number of required paged for the size the user need to allocate
	int Counter=0;
	Size_Of_Spaces=0;
	int i=0;
	int FirstIndex=0;
	int NewFirstIndex;


	if (size == 0 || size > (USER_HEAP_MAX - USER_HEAP_START))
	{
		First_add_allocated = NULL;
	}

	while(i<(KERNEL_HEAP_MAX-KERNEL_HEAP_START)/PAGE_SIZE)
	{
		 if(Visited[i].Flag1==0)
		{
			Counter++;
		}
		else
		{
			if(Counter)
			{
				Spaces[Size_Of_Spaces].add=(USER_HEAP_START+(FirstIndex*PAGE_SIZE));
				Spaces[Size_Of_Spaces].Size=(Counter*PAGE_SIZE);
				Spaces[Size_Of_Spaces].FirstIndex=FirstIndex;
				Size_Of_Spaces++;
			}
	   Counter=0;
		FirstIndex=i+1;

		}


			if(i==(((KERNEL_HEAP_MAX-KERNEL_HEAP_START)/PAGE_SIZE)-1))
			{
				NewFirstIndex=FirstIndex*PAGE_SIZE;
				Spaces[Size_Of_Spaces].add=(USER_HEAP_START+(NewFirstIndex));
				Spaces[Size_Of_Spaces].Size=(Counter*PAGE_SIZE);
				Spaces[Size_Of_Spaces].FirstIndex=FirstIndex;
				Size_Of_Spaces++;
			}
			i++;
		}
		uint32* add_back=NULL;
			for(int m=0 ; m< (Size_Of_Spaces-1) ; m++)
			{
				for(int j=0; j < (Size_Of_Spaces-m-1) ;j++)
				{
				  if(Spaces[j].add>Spaces[j+1].add)
				  {
					struct Info temp=Spaces[j];
					Spaces[j]=Spaces[j+1];
					Spaces[j+1]=temp;
				   }
				}
			}


			for(i=0;i<Size_Of_Spaces;++i)
			{
				if(Spaces[i].Size >= size)
				{
		          add_back=(uint32*)Spaces[i].add;
				   break;
				}
			}
			if(add_back != NULL)
			{
				int m=Spaces[i].FirstIndex;
				int sizee=(m+Req_Pages);
				Visited[m].add=(uint32)add_back;
				Visited[m].Size=ROUNDUP(size,PAGE_SIZE);
				Visited[m].FirstIndex=Spaces[i].FirstIndex;
				while(m<sizee)
				{
				Visited[m].Flag1=1;
				m++;
				}

			}

			 First_add_allocated =add_back;
			 if(First_add_allocated==NULL)
			 	{
			 		return NULL;
			 	}
			sys_allocateMem((uint32)First_add_allocated,size);
			return  (void*)First_add_allocated;



}

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable)
{
	//TODO: [PROJECT 2017 - [6] Shared Variables: Creation] smalloc() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("smalloc() is not implemented yet...!!");

	// Steps:
	//	1) Implement FIRST FIT strategy to search the heap for suitable space
	//		to the required allocation size (space should be on 4 KB BOUNDARY)
	//	2) if no suitable space found, return NULL
	//	 Else,
	//	3) Call sys_createSharedObject(...) to invoke the Kernel for allocation of shared variable
	//		sys_createSharedObject(): if succeed, it returns the ID of the created variable. Else, it returns -ve
	//	4) If the Kernel successfully creates the shared variable, return its virtual address
	//	   Else, return NULL

	//This function should find the space of the required range
	// ******** ON 4KB BOUNDARY ******************* //

	//Use sys_isUHeapPlacementStrategyFIRSTFIT() to check the current strategy

	//change this "return" according to your answer

	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName)
{
	//TODO: [PROJECT 2017 - [6] Shared Variables: Get] sget() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("sget() is not implemented yet...!!");

	// Steps:
	//	1) Get the size of the shared variable (use sys_getSizeOfSharedObject())
	//	2) If not exists, return NULL
	//	3) Implement FIRST FIT strategy to search the heap for suitable space
	//		to share the variable (should be on 4 KB BOUNDARY)
	//	4) if no suitable space found, return NULL
	//	 Else,
	//	5) Call sys_getSharedObject(...) to invoke the Kernel for sharing this variable
	//		sys_getSharedObject(): if succeed, it returns the ID of the shared variable. Else, it returns -ve
	//	6) If the Kernel successfully share the variable, return its virtual address
	//	   Else, return NULL
	//

	//This function should find the space for sharing the variable
	// ******** ON 4KB BOUNDARY ******************* //

	//Use sys_isUHeapPlacementStrategyFIRSTFIT() to check the current strategy

	//change this "return" according to your answer
	return 0;
}

// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address)
{
	//TODO: [PROJECT 2017 - [5] User Heap] free() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("free() is not implemented yet...!!");

	//you should get the size of the given allocation using its address
	//you need to call sys_freeMem()
	//refer to the project presentation and documentation for details
	    uint32 Size_Free=0;
	    int New_Free;
	    virtual_address=ROUNDDOWN(virtual_address,PAGE_SIZE);

		for(int i=0;i<(KERNEL_HEAP_MAX-KERNEL_HEAP_START)/PAGE_SIZE;i++)
	    {
		  if(Visited[i].add==(uint32)virtual_address )
		  {
			  if(Visited[i].Flag1)
			  {
			Size_Free=Visited[i].Size;
			Visited[i].add=0;
			Visited[i].Size=0;
			New_Free=(Size_Free/PAGE_SIZE);
			while(New_Free--)
			{
				Visited[i].Flag1=0;
				++i;
			}
			sys_freeMem((uint32)virtual_address,Size_Free);
			  }
		  }
	    }

}


//==================================================================================//
//============================== BONUS FUNCTIONS ===================================//
//==================================================================================//

//=============
// [1] sfree():
//=============
//	This function frees the shared variable at the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from main memory then switch back to the user again.
//
//	use sys_freeSharedObject(...); which switches to the kernel mode,
//	calls freeSharedObject(...) in "shared_memory_manager.c", then switch back to the user mode here
//	the freeSharedObject() function is empty, make sure to implement it.

void sfree(void* virtual_address)
{
	//TODO: [PROJECT 2017 - BONUS4] Free Shared Variable [User Side]
	// Write your code here, remove the panic and write your code
	panic("sfree() is not implemented yet...!!");

	//	1) you should find the ID of the shared variable at the given address
	//	2) you need to call sys_freeSharedObject()

}


//===============
// [2] realloc():
//===============

//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, in which case the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to malloc().
//	A call with new_size = zero is equivalent to free().

//  Hint: you may need to use the sys_moveMem(uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
//		which switches to the kernel mode, calls moveMem(struct Env* e, uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
//		in "memory_manager.c", then switch back to the user mode here
//	the moveMem function is empty, make sure to implement it.

void *realloc(void *virtual_address, uint32 new_size)
{
	//TODO: [PROJECT 2017 - BONUS3] User Heap Realloc [User Side]
	// Write your code here, remove the panic and write your code
	panic("realloc() is not implemented yet...!!");

}
