#pragma once
#include<SFML\Window.hpp>

// Window Settings
#define PX_WINDOW_DEFAULT_WIDTH 600
#define PX_WINDOW_DEFAULT_HEIGHT 400

#define PX_WINDOW_DEFAULT_RATIO WINDOW_DEFAULT_WIDTH / WINDOW_DEFAULT_HEIGHT


// Opengl Settings
#define PX_OPEN_GL_VERSION_MAJOR 4
#define PX_OPEN_GL_VERSION_MINOR 0
#define PX_OPENGL_PROFILE WindowSettings::Core
#define PX_OPENGL_sRGB true
#define PX_OPENGL_DEPTH_BITS 24
#define PX_OPENGL_STENCIL_BITS 8