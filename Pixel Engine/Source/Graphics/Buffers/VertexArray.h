#pragma once

namespace PX {
	namespace graphics {


		class VertexArray {
			unsigned int id;
							 
		public:

			VertexArray();
			~VertexArray();

			void Bind() const;
			void Unbind() const;
		};

	}
}