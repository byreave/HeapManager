# Heap Manager
This is a project where a customized memory allocate and deallocate system. Including a normal heap manager and a **fixed size allocator**.  
Operations in this heap manager include:
  
 - Allocation
 - Deallocation 
 - Collect fragmentation
 - Show available blocks for allocation.
 - Show allocated (outstanding) blocks.
## General ideas of a heap manager
Given a certain size of memory, the heap manager should give users to allocate a chosen amount of memory, release the memory that's been allocated and throw errors if no available.  

There are lots of ways to do this. In this project, I use the Block Descriptor struct to keep track of available and outstanding blocks in our heap.

    struct BlockDescriptor {
		void * m_pBlockStartAddr;
		size_t m_sizeBlock;
		BlockDescriptor * next;
	};

By maintaining two lists of available and outstanding blocks, we can return the address to user when there is a suitable block.  
## Features
**Garbage collection** is very important speaking of the efficiency of the heap manager. It can be done while allocating or individually.