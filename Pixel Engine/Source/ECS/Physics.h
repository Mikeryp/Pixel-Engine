#pragma once
#include"System.h"
#include"Component.h"

PX_Comp_decl(Physics);
class Physics;

class PhysicsManager : public Pixel::ECS::ECS_System
{
public:
	PX_System(PhysicsManager, Physics);

	virtual void Update(ComponentHandle c) override
	{
	}

	virtual void Init(ComponentHandle c) override
	{}

	virtual void Cleanup(ComponentHandle c) override
	{}
};

struct Physics : public Pixel::ECS::ECS_Component
{
	PX_Component(Physics);

	float x, y;
	float accX, accY;
	float velX, velY;
};

