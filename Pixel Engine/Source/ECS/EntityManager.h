#pragma once
#include"../Utils/Memory/PoolAllocater.h"
#include"../Utils/DataTypes.h"
#include"Entity.h"

namespace PX { namespace ECS {

	// NOT FOR NORMAL USE
	EntityID ECS_GenerateEntityID() {
		static uint32 next_id = -1;
		return ++next_id;
	}

	class EntityManager
	{
		static PX::Utils::Memory::PoolAllocater entities;
	public:

		static EntityID CreateEntity() 
		{

			Entity* e = (Entity*)(EntityManager::entities.Allocate()); // Allocation
			// Initialising data
			e->entity_id = ECS_GenerateEntityID();
			e->components = std::vector<ComponentID>();

			return e->entity_id;
		}


		// T is the type of component to be attached
		template<typename T>
		static ComponentID AttachComponent(EntityID entity_id)
		{
			
			// Grabbing required access
			ECS_System* sys = SystemManager::GetComponentSystem<T>();
			Entity* e = GetEntityPtr(entity_id);
			
			// Creating component.
			ComponentID comp_id = sys->CreateComponent(e->entity_id);
			e->components.push_back(comp_id);

			return comp_id;
		}

		template<typename T>
		static bool RemoveComponent(EntityID entity_id) {
			
			SystemID sys_id = T::system_id; // Getting the type of component.
			
			// Finding the entity.
			for (auto i = entities.begin(); i != entities.end(); i++) {
				Entity* e = (Entity*)(i.element);
				
				// Entity Match found.
				if (e->entity_id == entity_id) {
					
					// Searching through components
					for (auto j = e->components.begin(); j != e->components.end(); j++) {
						ECS_System* system = SystemManager::GetComponentSystem((*j));
						
						// Component Type match found
						if (system->GetSystemID() == sys_id) {
							ComponentID comp_id = (*j);
							e->components.erase(j); // Detaching from entity.

							// Destroying the component.
							system->DestroyComponent(comp_id);
						}
					}
				}
			}
		}



		// Pointer to the Entity. NOT FOR EXTERNAL USE
		static Entity* GetEntityPtr(EntityID id) 
		{
			
			// Finding entity
			for (auto i = EntityManager::entities.begin(); i != entities.end(); i++) {
				Entity* p = (Entity*)(i.element);
				
				// If the id matches,
				if (p->entity_id == id) {
					return p;
				}
			}

			// No ID match found.
			PX_Error("Invalid Entity ID: {}", id);
			return nullptr;
		}


	};
} }