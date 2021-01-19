#pragma once
#include"../Utils/DataTypes.h"
#include"../API/PX.h"
#include"Component.h"
#include<vector>



namespace PX { namespace ECS {

	// i am integrating the graphics module with ECS.
	// deleted group, decided they arent really needed.
	// renderable is about to be deleted, since only real renderable in 2d is sprite.
	// Making a sprite manager to transfer all the data manipulation.
	// Write the Entity Manager to manipulate entity data. (Get Entity Handle. etc)
	// Make this data oriented.

	struct Entity
	{
		uint32 entity_id;
		std::vector<ComponentID> components;
	};


} }