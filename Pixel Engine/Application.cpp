#include"Application.h"
#include"Source/Utils/Memory/PoolAllocater.h"

void Game::Init()
{ 
	// Loading Resources
	Pixel::graphics::TextureManager::LoadTextureFromFile("res/images/container.png", "Tex1");
	Pixel::graphics::TextureManager::LoadTextureFromFile("res/images/image.jpg", "Tex2");
	Pixel::graphics::TextureManager::LoadTextureFromFile("res/images/image.png", "Tex3");
}

void Game::Update() {
}