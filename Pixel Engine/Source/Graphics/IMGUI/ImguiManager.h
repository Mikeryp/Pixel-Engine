#pragma once
#include"../../../Pixel.h"


namespace PX { namespace graphics {

class ImguiManager {
	static Window* window;
	Texture* font_tex;
	
public:
	static bool Init(Window* window);
};


} }