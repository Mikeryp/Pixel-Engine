#include<GL\glew.h>
#include"Window.h"


namespace PX {


	Window::Window(const char* title,const unsigned int& width,const unsigned int& height,const WindowSettings& settings)
		: 
		window(sf::VideoMode(width,height), title, sf::Style::Default ,settings)
	{
		if (glewInit() != GLEW_OK) {
			printf("Cannot initialise GLEW\n");
			getchar();
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Window::~Window()
	{
		Input::DefaultClose(&this->window);
	}



	void Window::SetBackground(const unsigned char& r, const unsigned char& b, const unsigned char& g, const unsigned char& a)
	{
		glClearColor(r / 256.f, g / 256.f, b / 256.f, a / 256.f);
	}

	void Window::SetBackground(const unsigned char& shade, const unsigned char& a /*= 255*/)
	{
		glClearColor(shade / 256.f, shade / 256.f, shade / 256.f, a / 256.f);
	}

	void Window::SetIcon(const ImageData& data)
	{
		this->window.setIcon(data.width, data.height, data.pixels);
	}




	void Window::SetTitle(const char* title)
	{
		this->window.setTitle(title);
	}

	void Window::Update()
	{

		Input::EventLoop(); // @TODO: Remove this from here and put it 
							// in the Pixel's Update loop.
		this->SwapBuffers();
		this->Clear();
		this->UpdateWindowSize();

		this->counter.Update();
	}




	void Window::UpdateWindowSize()
	{
		sf::Vector2u dim = this->window.getSize();
		glViewport(0, 0, dim.x, dim.y);
	}

	WindowSettings Window::GetDefaults()
	{
		WindowSettings settings;
		settings.majorVersion = PX_OPEN_GL_VERSION_MAJOR;
		settings.minorVersion = PX_OPEN_GL_VERSION_MINOR;

		settings.attributeFlags = PX_OPENGL_PROFILE;
		settings.sRgbCapable = PX_OPENGL_sRGB;
		settings.depthBits = PX_OPENGL_DEPTH_BITS;
		settings.stencilBits = PX_OPENGL_STENCIL_BITS;

		return settings;
	}

}

