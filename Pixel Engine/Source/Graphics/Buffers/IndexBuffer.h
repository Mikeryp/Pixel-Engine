#pragma once
#include<vector>
#include"../../Utils/DataTypes.h"



namespace PX {
	namespace graphics {


		class IndexBuffer {

			uint32 id;
			uint32 indicies_count; // indicies counter.

		public:
			IndexBuffer();
			IndexBuffer(uint32* data, uint32 element_count);
			IndexBuffer(const IndexBuffer& i);
			~IndexBuffer();

		public:

			void ResetBuffer(uint32* data, uint32 element_count);

			void Bind() const;
			void Unbind() const;

			const uint32& GetID() const { return this->id; }
			const uint32& GetCount() const { return this->indicies_count; }
		};

	}

}