#include"SystemManager.h"
#include"../Utils/Memory/PoolAllocater.h"

// @TODO - Settings.h should contain constants.
PX::Utils::Memory::PoolAllocater PX::ECS::SystemManager::systems(sizeof(ECS_System), 50);


SystemID PX::ECS::SystemManager::RegisterSystem(ECS_System* system)
{
	ECS_System* c = (ECS_System*)SystemManager::systems.Allocate();
	return c->GetSystemID();
}

void PX::ECS::SystemManager::DeleteSystem(SystemID system)
{
	ECS_System* c = SystemManager::GetSystemPtr(system); // Receiving ptr to the system
	SystemManager::systems.Deallocate(c); // Deallocation
}

PX::ECS::ECS_System* PX::ECS::SystemManager::GetSystemPtr(SystemID id)
{
	// Iterating through all the systems to find a match for the id
	for (auto i = SystemManager::systems.begin(); i != SystemManager::systems.end(); i++) {
		ECS_System* p = (ECS_System*)(i.element);

		if (p->GetSystemID() == id)
			return (ECS_System*)p; // Match found. Return the system
	}
}
