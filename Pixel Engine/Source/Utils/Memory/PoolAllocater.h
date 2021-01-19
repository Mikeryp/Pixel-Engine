#pragma once
#include<vector>
#include<stdio.h>
#include"../Logger.h"
/*
   Page model:

       ..1...2...3...4...5...6...7...8...9..10...11..12..13..14..15..16..17..18..19..20..21..
	   .///	|//	|//	|	|//	|	|//	|//	|//	|//	|	|//	|	|	|	|	|	|	|	|	|	.
	   .///	|//	|//	|	|//	|	|//	|//	|//	|//	|	|//	|	|	|	|	|	|	|	|	|	.
	   .///	|//	|//	|	|//	|	|//	|//	|//	|//	|	|//	|	|	|	|	|	|	|	|	|	.
	   ......................................................................................

	   Here, 

	   Reserved memory := 
				The memory which is currently being used by the system, and is not in the 
				possession of the allocater.

		Allocated Memory := 
				The memory which is currently in the possession of the allocater. This memory 
				could be reserved by various systems, but the allocater is responsible for the 
				way the memory is reserved.


	   1 = memory start
			The first part of the memory allocated.
	   

*/

#include"MemAllocater.h"

namespace PX { 
	namespace Utils { namespace Memory {


		struct Page
		{
			void* memory_start; // the start of the memory page
			void* memory_next; // The next memory to be used OR the part of page left with 0 allocations
			std::vector<void*> returned_mem; // The free memory spots in the reserved area

			uint32 elem_size; // Size of one element
			uint32 occupied; // Total no of elements allocated

			uint32 page_size; // The total elements the page can hold

		public:

			Page(const size_t& size,const unsigned int& page_size)
				:
				page_size(page_size)
			{
				this->elem_size = size;
				this->memory_start = this->memory_next = malloc(this->elem_size * page_size);
				this->occupied = 0;
			}


			// Statistics of Allocater.
			uint32 GetTotalFreeBytes() { return (this->page_size - this->occupied) * this->elem_size; }
			uint32 GetTotalOccupiedBytes() { return this->occupied * this->elem_size;	}


		// Returns the memory 
		void* GetElement()
		{
			// If the page is full, allocation is not possible
			if (occupied >= this->page_size) {
				PX_Error("PoolAllocater Object: Unable to Initialise memory - No space in page");
				return (void*)0;
			}

			// If some spots are empty in the filled area
			if (returned_mem.size() > 0) {
				void* mem = this->returned_mem.back();

				this->returned_mem.pop_back();
				return mem;
			}

			// Give memory away from the free area.
			void* element = this->memory_next;
			this->memory_next = (void*)(((char*)this->memory_next) + this->elem_size);
			this->occupied++;

			return element;
		}

		// Returns the memory to the page.
		bool ReturnElement(void* mem)
		{
			if (this->InPage(mem) && mem < this->memory_next) 
			{
				this->returned_mem.push_back(mem);
				this->occupied--;
				return true;
			}

			PX_Warning("PoolAllocater Object: Unable to return Memory");
			return false;
		}

		// Checks if a given memory is in the page
		bool InPage(void* mem)
		{
			void* start = this->memory_start;
			void* end = (void*)((char*)this->memory_start + (this->page_size * this->elem_size) );

			// If the mem address is in between the page start and page end, 
			// then it is in the page
			if ( mem >= start && mem < end )
				return true;

			PX_Error("PoolAllocater Object: memory {} not found in page.", &mem);
			return false;
		}


		~Page()
		{
			free(this->memory_start);
			PX_Info("PoolAllocater Object: {} bytes of memory freed.", this->page_size * this->elem_size);
		}

	};



	class PoolAllocater : public MemAllocater
	{
		uint32 elem_size; // The size of the elements to be allocated
		Page* page;
		const uint32 page_size; // No of elements in one page


		struct Iterator; 
		friend struct Iterator;

		
		// A structure provided for iterating through all the elements of the page 
		struct Iterator
		{
			PoolAllocater* parent;
			void* element;
			
			void* operator -> ()
			{
				return (element);
			}

			bool operator == (const Iterator& iter)
			{
				if (this->parent == iter.parent && this->element == iter.element)
					return true;
				return false;
			}

			bool operator != (const Iterator& iter)
			{
				if (this->parent == iter.parent && this->element != iter.element)
					return true;
				return false;
			}

			void operator = (const Iterator& iter)
			{
				this->parent = iter.parent;
				this->element = iter.element;
			}

			void operator ++ ()
			{
				this->element  = ((char*)this->element + this->parent->elem_size);
			}

			void operator ++ (int)
			{
				this->element = ((char*)this->element + this->parent->elem_size);
			}
		};


	public:

		PoolAllocater(uint32 elem_size = 4,uint32 page_size = 100)
			:
			elem_size(elem_size),
			page_size(page_size),
			page(new Page(elem_size, page_size))
		{
		}

		~PoolAllocater()
		{
			delete this->page;
		}


		// allocates a memory block of the given size for usage.
		virtual  void* Allocate()
		{
			return this->page->GetElement();
		}


		// returns the memory to free area.
		virtual bool Deallocate(void* elem)
		{
			if (this->page->ReturnElement(elem))
				return true;
			return false;
		}
		
		// returns the very first element of the first page
		Iterator begin()
		{
			Iterator iter;
			iter.element = this->page->memory_start;
			iter.parent = this;
			return iter;
		}

		// returns the very last element of the very last page. 
		Iterator end()
		{
			//void* end = (char*)this->page->memory_start + (this->page->page_size * this->page->elem_size);
			void* end = this->page->memory_next;
			// This is to prevent processing of data that is not in use.

			Iterator iter;
			iter.element = end;
			iter.parent = this;
			return iter;
		}

		//returns the total no of bytes occupied for usage.
		virtual uint32 GetTotalBytesReserved() 
		{
			return this->page->GetTotalOccupiedBytes();
		}

		// returns the total memory allocated by the allocater.
		virtual uint32 GetTotalBytesAllocated()
		{
			return  this->elem_size * this->page_size;
		}

		// returns total bytes unused
		virtual uint32 GetTotalFreeBytes()
		{
			return this->page->GetTotalFreeBytes();
		}
	};

} } }