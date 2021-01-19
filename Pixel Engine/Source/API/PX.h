#pragma once

//Audio includes
//#include"../Audio/AudioManager.h"
#include"../Audio/Music.h"
#include"../Audio/Sound.h"
#include"../Audio/Playable.h"

//Math includes
#ifdef PX_3D
#include"Quaternion.h"
#endif
#include"Vector.h"
#include"Math_Functions.h"
#include"Matrix.h"
#include"Constants.h"


// Input includes
#include"../Window/Input.h"
#include"../Window/WindowSettings.h"


// Graphics includes
#include"../Graphics/Group.h"
#include"../Graphics/ImageData.h"
#include"../Graphics/Render Space.h"
#include"../Graphics/Renderable.h"
#include"../Graphics/TextureManager.h" // @TODO : Probably not required
#include"../Graphics/Sprite.h"
#ifdef PX_3D
#include"../Graphics/Camera/Camera3D.h"
#else
#include"../Graphics/Camera/Camera2D.h"
#endif
#include"../Graphics/Layers/Tile Layer.h"
#include"../Graphics/Layers/Background Layer.h"
#include"../Graphics/Layers/Layer.h"


// The Engine class
#include"../EngineSettings.h"
#include"../../Pixel.h"