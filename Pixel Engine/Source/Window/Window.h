#include<GL/glew.h>

#include<SFML\OpenGL.hpp>
#include<SFML\Window.hpp>

#include"WindowSettings.h"
#include"Input.h"

#include"../Graphics/ImageData.h"
#include"FPS_Counter.h"
#include"Vector.h"

namespace PX {

	class Window
	{
		sf::Window window;
		FPS_Counter counter;

	public:

		friend class Input;

		Window(const char* title, const unsigned int& width = PX_WINDOW_DEFAULT_WIDTH, const unsigned int& height = PX_WINDOW_DEFAULT_HEIGHT, const WindowSettings& settings = Window::GetDefaults());
		~Window();

		void SetBackground(const unsigned char& r, const unsigned char& b, const unsigned char& g, const unsigned char& a = 255);
		void SetBackground(const unsigned char& shade, const unsigned char& a = 255);

		void SetIcon(const ImageData& pixels);
		void SetTitle(const char* title);

		bool IsOpen() const { return this->window.isOpen(); }
		void Update();

		double GetFPS() const { return this->counter.GetFPS(); }
		Math::Vector2 GetSize() const
		{
			float x = this->window.getSize().x;
			float y = this->window.getSize().y;

			return Math::Vector2(x, y);
		}

		const sf::Window& GetSFWindow() const { return this->window; }



	private:
		void UpdateWindowSize();
		inline void Clear() { glClear(GL_COLOR_BUFFER_BIT); }
		inline void SwapBuffers() { this->window.display(); }


	public:
		static WindowSettings GetDefaults();
	};


}