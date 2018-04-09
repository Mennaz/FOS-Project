#include <inc/memlayout.h>
#include <kern/kheap.h>
#include <kern/memory_manager.h>

//NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)

//=================================================================================//
//============================ REQUIRED FUNCTION ==================================//
//=================================================================================//
struct AddressData
{
	 uint32 Size;
	 uint32 First_Address;
};
struct AddressData All_Addresses[(KERNEL_HEAP_MAX - KERNEL_HEAP_START)/PAGE_SIZE];
int arr_counter=0 ;
uint32 firstFreeVAInKHeap = KERNEL_HEAP_START;
void* kmalloc(unsigned int size)
{
    uint32 first_add= firstFreeVAInKHeap;
	All_Addresses[arr_counter].Size = size ;
	All_Addresses[arr_counter].First_Address = firstFreeVAInKHeap ;
	arr_counter++;
	if(size < KERNEL_HEAP_MAX-firstFreeVAInKHeap)
	{
		uint32 tmp =firstFreeVAInKHeap +size ;
		for(; firstFreeVAInKHeap<tmp ; firstFreeVAInKHeap+=PAGE_SIZE)
		{
			struct Frame_Info *ptr_frame_info = NULL;
			allocate_frame(&ptr_frame_info);
			map_frame(ptr_page_directory,ptr_frame_info,(void*)firstFreeVAInKHeap,PERM_WRITEABLE);

		}
		return (void*) first_add;
	}
	else
	{
		return NULL ;
	}
	//TODO: [PROJECT 2017 - [1] Kernel Heap] kmalloc()
		// Write your code here, remove the panic and write your code
		//panic("kmalloc() is not implemented yet...!!");
		//NOTE: Allocation is continuous increasing virtual address
		//NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)
		//refer to the project presentation and documentation for details
		//TODO: [PROJECT 2017 - BONUS1] Implement a Kernel allocation strategy
		// Instead of the continuous allocation/deallocation, implement both
		// FIRST FIT and NEXT FIT strategies
		// use "isKHeapPlacementStrategyFIRSTFIT() ..." functions to check the current strategy
		//change this "return" according to your answer
		//return NULL;
}

void kfree(void* virtual_address)
{
	//TODO: [PROJECT 2017 - [1] Kernel Heap] kfree()
	// Write your code here, remove the panic and write your code
	//panic("kfree() is not implemented yet...!!");
	//you need to get the size of the given allocation using its address
	//refer to the project presentation and documentation for details
	uint32 size=0;
		for(int i=0 ; i<arr_counter; i++)
		{
		if(All_Addresses[i].First_Address==(uint32)virtual_address)
			{
				size=All_Addresses[i].Size;
				uint32 tmp=size+(uint32)virtual_address ;
				tmp=ROUNDUP(tmp, PAGE_SIZE) ;
				for(; (uint32)virtual_address< tmp; virtual_address+=PAGE_SIZE)
				{
					unmap_frame(ptr_page_directory,(void*)virtual_address);
				}
			All_Addresses[i].First_Address=-1 ;
			All_Addresses[i].Size=-1 ;
			return ;
			}
		}
}
unsigned int kheap_virtual_address(unsigned int physical_address)
{

	//TODO: [PROJECT 2017 - [1] Kernel Heap] kheap_virtual_address()
	// Write your code here, remove the panic and write your code
	//panic("kheap_virtual_address() is not implemented yet...!!");

	//return the virtual address corresponding to given physical_address
	//refer to the project presentation and documentation for details

	//change this "return" according to your answer
	//return 0;
	struct Frame_Info * frames_info_pa=to_frame_info(physical_address);
	uint32 start = KERNEL_HEAP_START;
	for(int i=KERNEL_HEAP_START; i<firstFreeVAInKHeap;i+=PAGE_SIZE)
		{
		uint32 *ptr_page_table = NULL;
		struct Frame_Info * frames_info_heap=get_frame_info(ptr_page_directory ,(int*)start , &ptr_page_table);
		if(frames_info_pa==frames_info_heap)
		{
		return start;
		}
		start+=PAGE_SIZE;
		}
	return 0;
        }
unsigned int kheap_physical_address(unsigned int virtual_address)
{
	//TODO: [PROJECT 2017 - [1] Kernel Heap] kheap_physical_address()
	// Write your code here, remove the panic and write your code
	//panic("kheap_physical_address() is not implemented yet...!!");
	//return the physical address corresponding to given virtual_address
	//refer to the project presentation and documentation for details
	//change this "return" according to your answer
virtual_address = ROUNDDOWN(virtual_address,PAGE_SIZE);
uint32 pa , entry;
uint32 *ptr_page_table = NULL;
get_page_table(ptr_page_directory,(void*)virtual_address, &ptr_page_table);
if (ptr_page_table != NULL)
{
  entry = ptr_page_table[PTX( virtual_address)] >> 12;
  pa = entry * PAGE_SIZE;
}
return pa;
}
//=================================================================================//
//============================== BONUS FUNCTION ===================================//
//=================================================================================//
// krealloc():

//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, in which case the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to kmalloc().
//	A call with new_size = zero is equivalent to kfree().

void *krealloc(void *virtual_address, uint32 new_size)
{
	//TODO: [PROJECT 2017 - BONUS2] Kernel Heap Realloc
	// Write your code here, remove the panic and write your code

	panic("krealloc() is not implemented yet...!!");
	return NULL;
}
