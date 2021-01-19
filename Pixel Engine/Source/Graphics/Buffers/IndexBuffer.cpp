#include<GL\glew.h>
#include"IndexBuffer.h"

#include<cstdlib>
#include<cstdio>
#include<string.h>

namespace PX {
	namespace graphics {


		IndexBuffer::IndexBuffer()
			:
			indicies_count(0)
		{
			glGenBuffers(1, &this->id);
		}



		IndexBuffer::IndexBuffer(uint32* data,uint32 count)
			:
			indicies_count(count)
		{
			glGenBuffers(1, &this->id);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * this->indicies_count, data, GL_STATIC_DRAW);
		}

		IndexBuffer::IndexBuffer(const IndexBuffer& i)
			:
			indicies_count(i.GetCount())
		{
			glGenBuffers(1, &this->id);

			uint32* dt = (uint32*)malloc(sizeof(uint32) * i.GetCount());
			
			// Getting i index buffer from GPU.
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i.GetID());

			void* data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_BUFFER);
			memcpy(dt, data, sizeof(uint32) * i.GetCount());
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
				
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * this->indicies_count, dt, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			free(dt);
		}



		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &this->id);
		}





		void IndexBuffer::ResetBuffer(uint32* data,uint32 count)
		{
			this->indicies_count = count;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * this->indicies_count, data, GL_STATIC_DRAW);
		}

		void IndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
		}

		void IndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}

}