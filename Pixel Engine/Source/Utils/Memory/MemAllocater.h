#pragma once

namespace PX {
	namespace Utils { namespace Memory {

	class MemAllocater
	{
	protected:
		MemAllocater() {}
		virtual ~MemAllocater() {}
	
	public:
		virtual void* Allocate() = 0;
		virtual bool Deallocate(void*) = 0;
	
		virtual uint32 GetTotalBytesReserved() = 0;
		virtual uint32 GetTotalBytesAllocated() = 0;
		virtual uint32 GetTotalFreeBytes() = 0;
	
	};

	}}
}
