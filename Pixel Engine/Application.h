#pragma once

#include"Source/API/PX_Game.h"
#include"Source/API/PX.h"

#include"Source/Utils/Memory/PoolAllocater.h"

class Game : public Pixel::PX_Game
{
	Pixel::graphics::Sprite* s1;
	Pixel::graphics::Sprite* s2;
	Pixel::graphics::Sprite* s3;

	Pixel::Utils::Memory::PoolAllocater allocater;
	uint32 i;

public:
	void Update() override;
	void Init() override;

};
