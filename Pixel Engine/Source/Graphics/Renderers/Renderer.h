#pragma once
#include"../Buffers/VertexArray.h"
#include"../Buffers/VertexBuffer.h"
#include"../Buffers/IndexBuffer.h"
#include"../Renderable.h"
#include"Matrix.h"

#include<set>

namespace PX {
	namespace graphics {


		class Sprite;
		class Group;
		class Renderable;
		class Text;


		class Renderer
		{
		protected:
			VertexArray vao;

		public:
			Renderer() : vao() {};
			virtual ~Renderer() {}

			// Renderer interface
			virtual void Begin() = 0;
			virtual void End() = 0;

			virtual void Submit(const Sprite* sprite, const Math::mat4& transform = Math::mat4::identity()) = 0;
			virtual void Submit(const Sprite* sprites,uint32 count) {}

			// primitive shapes
			virtual void DrawLine(const Math::Vector3& v1, const Math::Vector3& v2, const Math::Vector4& color = Math::Vector4(1,1,1,1)) {}
			virtual void DrawRect(const Math::Vector3& pos, const Math::Vector3& dimension) {}
			virtual void DrawCircle(const Math::Vector3& position, const float& radius, const float& density) {}
			virtual void DrawTriangle(const Math::Vector3& v1, const Math::Vector3& v2, const Math::Vector3& v3) {}

			// Text Rendering interface
			virtual void DrawString(const Text& text, const Math::Vector3 position, const Math::Vector2& dimensions, const Math::mat4& transform = Math::mat4::identity(), const Math::Vector4& color = Math::Vector4(1, 1, 1, 1)) {}

			virtual void Render() = 0;
		};
	}
}
