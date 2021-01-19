#pragma once
#include<vector>
#include<GL/glew.h>

#include"Vertex.h"



namespace PX {

	namespace graphics {

		class VertexBuffer {

		private:
			uint32 id;
   
		public:
					  
			VertexBuffer();
			VertexBuffer(Vertex* data, uint32 size, uint32 mode = GL_STATIC_DRAW);
			VertexBuffer(uint32 size,uint32 mode = GL_STATIC_DRAW);
			~VertexBuffer();		    

			void ResetBuffer(Vertex* data, uint32 count, uint32 mode = GL_STATIC_DRAW);
			void ResetBuffer(uint32 size, uint32 mode = GL_STATIC_DRAW);

			std::vector<Vertex> GetVerticies() const;

			void Bind() const;
			void Unbind() const;
		};

	}

}