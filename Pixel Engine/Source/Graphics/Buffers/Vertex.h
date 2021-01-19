#pragma once
#include"Vector.h"

namespace PX {
	namespace graphics {

		struct Vertex {		  
			Math::Vector3 vertex;
			Math::Vector4 color;
			Math::Vector2 uv;
			
			float tex_id;
		};


	}
}
