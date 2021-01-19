#include"Input.h"
#include"Window.h"

#include"Vector.h"

namespace PX {

	Window* Input::window;
	WindowCloseCallback Input::close_callback;

	sf::Event Input::e;
	std::map<Key, bool> Input::key_status;

	void (*Input::key_press_func)(const Key& key) = NULL;
	void(*Input::key_release_func)(const Key& key) = NULL;


	void Input::Init(Window* window)
	{
		Input::window = (Window*)window;
		Input::close_callback = Input::DefaultClose;

		for (int i = 0; i < Key::KeyCount; i++)
			Input::key_status[(Key)i] = false;
	}





	void Input::CleanUp()
	{
		if (Input::window->window.isOpen())
			(*Input::close_callback)(&Input::window->window);
	}

	void Input::EventLoop()
	{
		while (Input::window->window.pollEvent(Input::e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
					(*Input::close_callback)(&Input::window->window);
				break;

				case sf::Event::KeyPressed:
					if (!Input::key_status[e.key.code]) 
					{
						Input::key_status[e.key.code] = true;
						
						if (Input::key_press_func)
							(Input::key_press_func)(e.key.code);
					}

				break;

				case sf::Event::KeyReleased:
					if (Input::key_status[e.key.code])
					{
						Input::key_status[e.key.code] = false;

						if (Input::key_release_func)
							(*Input::key_release_func)(e.key.code);
					}
				break;
			}
		}
	}

	bool Input::isKeyPressed(const Key& key)
	{
		return Input::key_status[key];
	}  

	void Input::SetCloseCallback(WindowCloseCallback function)
	{
		Input::close_callback = function;
	}

	void Input::SetKeyPressCallback(void(*function)(const Key&))
	{
		Input::key_press_func = function;
	}

	void Input::SetKeyReleaseCallback(void(*function)(const Key&))
	{
		Input::key_release_func = function;
	}

	Math::Vector2 Input::GetMousePosition()
	{
		sf::Vector2i pos = sf::Mouse::getPosition(Input::window->window);
		return Math::Vector2(pos.x, pos.y);
	}

}