#pragma once

// This class fires up the Pixel

#include"Source\Window\Window.h"
#include"Source/ECS/System.h"
#include"Source/Graphics/Render Space.h"
#include"Source/API/PX_Game.h"
#include"Source/ECS/SystemManager.h"

namespace Pixel {

	namespace Entity { class GameObject; class Entity; }

	struct PixelSettings
	{
		unsigned int window_width, window_height;
		unsigned int renderspace_width, renderspace_height;
		WindowSettings window_settings;
		std::string window_title;
	};



	class Pixel
	{
		static Window* window;
		static graphics::RenderSpace* render_space;
		static PX_Game* game;

		ECS::SystemManager systems;

	public:

		static PixelSettings settings;

		static void SetupGame(PX_Game* game);
		static void Init(const PixelSettings& settings);
		static void Start();
		static void Loop();
		static void CleanUp();


		friend double GetWindowFPS();
	};

}