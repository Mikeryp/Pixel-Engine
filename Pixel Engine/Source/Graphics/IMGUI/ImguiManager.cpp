#include "ImguiManager.h"
#include <imgui.h> 
#include <SFML/Window/Joystick.hpp>

namespace PX { namespace graphics {

	bool ImguiManager::Init(Window* window)
	{
		ImguiManager::window = window;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// init keyboard mapping
		io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
		io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
		io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
		io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
		io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
		io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
		io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
		io.KeyMap[ImGuiKey_Insert] = sf::Keyboard::Insert;
#ifdef ANDROID
		io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::Delete;
#else
		io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
		io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
#endif
		io.KeyMap[ImGuiKey_Space] = sf::Keyboard::Space;
		io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
		io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
		io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
		io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
		io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
		io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
		io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
		io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;

		io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
		//s_joystickId = getConnectedJoystickId();

		//for (unsigned int i = 0; i < ImGuiNavInput_COUNT; i++) {
		//	s_joystickMapping[i] = NULL_JOYSTICK_BUTTON;
		//}

		//initDefaultJoystickMapping();

		// init rendering
		ImVec2 v{window->GetSize().x, window->GetSize().y};
		io.DisplaySize = v;

		if (s_fontTexture) { // delete previously created texture
			delete s_fontTexture;
		}
		s_fontTexture = new sf::Texture;

		if (loadDefaultFont) {
			// this will load default font automatically
			// No need to call AddDefaultFont
			UpdateFontTexture();
		}

		s_windowHasFocus = window.hasFocus();
	}


} }