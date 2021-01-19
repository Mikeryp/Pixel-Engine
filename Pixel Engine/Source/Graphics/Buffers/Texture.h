#pragma once
#include<GL/glew.h>

#include"Vector.h"
#include"../ImageData.h"


namespace PX {
	namespace graphics {

		class Texture
		{
			unsigned int texID;
			ImageData image;

		public:
			Texture();
			Texture(const unsigned int& texID);
			Texture(const ImageData& image);
			Texture(ImageData&& image);

			Texture(Texture&&);
			Texture(const Texture&);

			~Texture();

			unsigned short GetWidth() const { return this->image.width; }
			unsigned short GetHeight() const { return this->image.height; }
			unsigned int GetID() const { return this->texID; }

			void Bind() const;
			void Unbind() const;

			void Reset(const ImageData& image);
			void Reset(ImageData&& image);

			inline void BufferTexture()
			{
				glBindTexture(GL_TEXTURE_2D, this->texID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				// NOTE:
				// 6404 = GL_GREEN
				// GL_GREEN + 3 = GL_RGB
				// GL_GREEN + 4 = GL_RGBA
				glTexImage2D(GL_TEXTURE_2D, 0, 6404 + this->image.BPP, this->image.width, this->image.height, 0, 6404 + this->image.BPP, GL_UNSIGNED_BYTE, this->image.pixels);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		};
	}
}