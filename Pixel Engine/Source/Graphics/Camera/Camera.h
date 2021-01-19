#pragma once
#include"Matrix.h"

namespace PX {
	namespace graphics {

		class Camera
		{
		protected:
			Math::mat4 projection;
			Math::mat4 view;

		protected:
			Camera(const Math::mat4& projection, Math::mat4& view = Math::mat4(1))
				: projection(projection), view(view)
			{}

		public:
			virtual ~Camera() {}

		public:

			const Math::mat4& GetViewMat() const { return this->view; }
			const Math::mat4& GetProjectionMat() const { return this->projection; }
		};

	}
}