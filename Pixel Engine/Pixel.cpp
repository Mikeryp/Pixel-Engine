#include"Pixel.h"
#include"Source\Audio\AudioManager.h"

namespace Pixel {

	Window* Pixel::window;
	graphics::RenderSpace* Pixel::render_space;
	PX_Game* Pixel::game;
	std::vector<ECS::ECS_System> Pixel::systems;



	void Pixel::SetupGame(PX_Game* game)
	{
		Pixel::game = game;
	}


	void Pixel::Init(const PixelSettings& settings)
	{
		Pixel::window = new Window(settings.window_title.c_str(), settings.window_width, settings.window_height);
		Pixel::render_space = new graphics::RenderSpace(settings.renderspace_width, settings.renderspace_height);

		// Initialising modules.
		Audio::AudioManager::Init();
		Input::Init(Pixel::window);

		// Initialising Systems
	}

	void Pixel::Start()
	{
		Pixel::game->Init();

		while (Pixel::window->IsOpen())
			Pixel::Loop();
	}

	void Pixel::Loop()
	{
		Audio::AudioManager::Update();

		Pixel::window->Update();
		Pixel::game->Update();
		Pixel::render_space->Render();
	}

	void Pixel::CleanUp()
	{
		delete Pixel::window;
		delete Pixel::render_space;

		Audio::AudioManager::CleanUp();
	}

	double GetWindowFPS() { return Pixel::window->GetFPS(); }

}
