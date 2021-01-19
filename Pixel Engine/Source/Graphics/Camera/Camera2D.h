#pragma once

#include "Matrix.h"
#include "Vector.h"

#include"Camera.h"


namespace PX {
	namespace graphics {

		class Camera2D : public Camera
		{
		public:
			Camera2D(const short& x, const short& y, const short& width, const short& heigth);
			Camera2D();

			void SetPosition(const short& x, const short& y);
			const Math::Vector2& GetPosition() const;

			//void Magnify(const float& val);
			//void Rotate(const float& val);
		};
	}
}