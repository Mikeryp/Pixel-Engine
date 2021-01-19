#include"VertexBuffer.h"
#include"../../Utils/DataTypes.h"


namespace PX {

	namespace graphics {

		VertexBuffer::VertexBuffer()
		{
			glGenBuffers(1, &this->id);
		}

		VertexBuffer::VertexBuffer(Vertex* data, uint32 size, uint32 mode)
		{
			glGenBuffers(1, &this->id);					                

			glBindBuffer(GL_ARRAY_BUFFER, this->id);
			glBufferData(GL_ARRAY_BUFFER, size, data, mode);
		}

		VertexBuffer::VertexBuffer(uint32 size, uint32 mode)
		{	 
			glGenBuffers(1, &this->id);

			glBindBuffer(GL_ARRAY_BUFFER, this->id);
			glBufferData(GL_ARRAY_BUFFER, size, NULL, mode);
		}

		VertexBuffer::~VertexBuffer()
		{				  
			glDeleteBuffers(1, &this->id);
		}







		void VertexBuffer::ResetBuffer(Vertex* data, uint32 count, uint32 mode)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
			glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
		}


		void VertexBuffer::ResetBuffer(uint32 size,uint32 mode)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
			glBufferData(GL_ARRAY_BUFFER, size, NULL, mode);
		}

		void VertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}

		void VertexBuffer::Unbind()	const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}

}