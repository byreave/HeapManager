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
### Position of block descriptors
In this project, I allocate the block descriptors at the bottom of our heap and use two lists to keep track of whether it's allocated and its size.  
![Position of block descriptors](https://i.imgur.com/g85K0qT.png)  
### Garbage collection
**Garbage collection** is very important speaking of the efficiency of the heap manager. It can be done while allocating or individually.  
The idea to collect released memory is to check the available list of block descriptors, and if there are two blocks of continuous address, combine them into one bigger block.
### Alignment
The heap manager in this project supports alignment while allocating. Supported alignments: 4, 8, 16, 32, 64 bytes.
### Fillvalues and guardbanding
In debug mode, there are several ways to detect illegal memory usage to prevent further danger in code. Fillvalues and guardbanding is such ways to tell if and in which way the user is wrong access the memory.  
![](https://i.imgur.com/M4yth18.png)

    static unsigned char _bNoMansLandFill = 0xFD; /* fill no-man's land with this */
	static unsigned char _bAlignLandFill  = 0xED; /* fill no-man's land for aligned routines */ 
	static unsigned char _bDeadLandFill   = 0xDD; /* fill free objects with this */ 
	static unsigned char _bCleanLandFill  = 0xCD; /* fill new objects with this */ 
