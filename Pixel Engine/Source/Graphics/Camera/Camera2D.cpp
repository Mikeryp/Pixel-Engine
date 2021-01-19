#include "Camera2D.h"

namespace PX {
	namespace graphics {

		Camera2D::Camera2D()
			:
			Camera(Math::mat4::orthographic(0, 600, 0, 400, 0, 1))
		{
		}

		Camera2D::Camera2D(const short& x, const short& y, const short& width, const short& height)
			:
			Camera(Math::mat4::orthographic(x, width, y, height, 0, 1))
		{
		}

		void Camera2D::SetPosition(const short& x, const short& y)
		{
			this->view.column[3].x = x;
			this->view.column[3].y = y;
		}

		const Math::Vector2& Camera2D::GetPosition() const
		{
			return *((Math::Vector2*)&this->view.column[3].x);
		}

	}
}