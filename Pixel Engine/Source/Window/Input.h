#pragma once
#include<map>

#include"Vector.h"
#include<SFML\Window.hpp>
		   

namespace PX {

	class Window;

	typedef sf::ContextSettings WindowSettings;
	typedef sf::Keyboard::Key Key;
	typedef void(*WindowCloseCallback)(sf::Window*);

	class Input
	{
		static Window* window;
		static WindowCloseCallback close_callback;

		static sf::Event e;
		static std::map<Key, bool> key_status;

		static void(*key_press_func)(const Key& key);
		static void(*key_release_func)(const Key& key);
		
		//@TODO : Implement these
		static void(*window_active)();
		static void(*window_inactive)();

	public:
		static void Init(Window* window);
		static void CleanUp();

		static void EventLoop();
		static bool isKeyPressed(const Key& key);
		static void SetCloseCallback(WindowCloseCallback function);

		static Math::Vector2 GetMousePosition();

		static void DefaultClose(sf::Window* window) { window->close(); }
		static void SetKeyPressCallback(void(*function)(const Key&));
		static void SetKeyReleaseCallback(void(*function)(const Key&));
	};


}