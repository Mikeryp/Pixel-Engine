#pragma once

#include<vector>

#include"System.h"
#include"Component.h"
#include"System.h"
#include"../Utils/DataTypes.h"

namespace PX { namespace ECS {


class SystemManager {
	static PX::Utils::Memory::PoolAllocater systems; // A contiguous array of Systems.

public:
	static SystemID RegisterSystem(ECS_System* system); //Registers the system for use.
	static void DeleteSystem(SystemID system); // Deletes the system.

	// Returns a pointer to the system. INTERNAL USE ONLY.
	static ECS_System* GetSystemPtr(SystemID id); 

	template<typename T>
	static const ECS_System* GetComponentSystem()
	{
		const SystemID s_id = T::system_id; // The id to be searched for.
		ECS_System* p = SystemManager::GetSystemPtr(s_id);

		// No System was found which processes this component.
		if (p == nullptr) {
			PX_Error("No System found for component: ", T::ToString());
		}

		return p;
	}

	static const ECS_System* GetComponentSystem(ComponentID component_id)
	{
		for (auto i = SystemManager::systems.begin(); i != SystemManager::systems.end(); i++) {
			ECS_System* system = (ECS_System*)(i.element);
			
			// Searching for the component id in this system.
			for (auto e = system->elements.begin(); e != system->elements.end(); e++) {
				ECS_Component* c = (ECS_Component*)(e.element);
				
				// Component exists in the system.
				if (c->component_id == component_id) {
					return system;
				}
			}
		}
	}
};


} }