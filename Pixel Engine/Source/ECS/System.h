#pragma once
#include"../Utils/Memory/PoolAllocater.h"
#include"Component.h"
#include"../Utils/Logger.h"
#include"../Utils/DataTypes.h"

#define PX_Comp_decl(component_name)\
		SystemID component_name::system_id;

#define PX_System(manager_name, component_name) \
	friend class SystemManager;\
	manager_name()\
		:\
		ECS_System(sizeof(component_name))\
		{\
			component_name::system_id = this->system_id;\
		}\

namespace PX { namespace ECS {

	// The Systems are going to be initialized in the init method of the Engine class
	// All the Systems are going to be registered during initialization. 
	//
	// @TODO: Runtime System Registration.

	uint32 ECS_GetSystemID()
	{
		static uint32 nextID = 0;
		return nextID++;
	}


	class ECS_System
	{

		friend class SystemManager;
	protected:
		SystemID system_id;
		PX::Utils::Memory::PoolAllocater elements; // Allocator for components 
	protected:
	public:
		
		ECS_System(uint32 elem_size)
			:
			elements(elem_size),
			system_id(ECS_GetSystemID())
		{}

		virtual ~ECS_System() {}

		void ECS_Update()
		{
			for (auto i = elements.begin(); i != elements.end(); i++) {
				this->Update((ComponentHandle)(i.element));
			}
		}
		void ECS_Cleanup() {
			for (auto i = elements.begin(); i != elements.end(); i++) {
				this->Cleanup((ComponentHandle)(i.element));
			}
		}


		// Function called for every component object created
		virtual void Update(ComponentHandle) {};
		virtual void Init(ComponentHandle) {};
		virtual void Cleanup(ComponentHandle) {};


		uint32 GetSystemID() { return this->system_id; }
		
		// Called by an Entity
		ComponentID CreateComponent(uint32 entity_id)
		{
			ECS_Component* element = (ECS_Component*)this->elements.Allocate();
			element->Init(this->system_id, entity_id);
			this->Init((ComponentHandle)element);
			return element->component_id;
		}

		ComponentHandle GetComponentHandle(ComponentID id)
		{
			for (auto i = this->elements.begin(); i != this->elements.end(); i++)
			{
				if (((ECS_Component*)(i.element))->component_id == id)
					return ((ComponentHandle)(i.element));
			}

			// If the element was not found, it has not been created.
			PX_Warning("COMPONENT_ID: {}      SYSTEM_ID: {}  --> Not Found", id, this->system_id);
			return nullptr;
		}

		bool DestroyComponent(ComponentID component_id)
		{
			return this->DestroyComponent(this->GetComponentHandle(component_id));
		}
		bool DestroyComponent(ComponentHandle component_handle)
		{
			return this->elements.Deallocate(component_handle);
		}

		EntityID GetComponentEntity(ComponentID component_id)
		{
			ECS_Component* c = (ECS_Component*)this->GetComponentHandle(component_id);
			return c->entity_id;
		}
	};



} }