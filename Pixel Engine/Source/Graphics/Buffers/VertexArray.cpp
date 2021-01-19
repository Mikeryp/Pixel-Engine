#include"VertexArray.h"
#include<GL/glew.h>

namespace PX {
	namespace graphics {

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &this->id);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &this->id);
		}


		// // // // // // // 
		// 
		// Methods
		// 
		// // // // // // //


		void VertexArray::Bind() const
		{
			glBindVertexArray(this->id);
		}

		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}

	}

}