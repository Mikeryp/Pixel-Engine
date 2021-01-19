/*
	@Info :- Low Level opengl texture wrappers
*/

#include<GL\glew.h>
#include<cstring>

#include"Texture.h"

namespace PX {
	namespace graphics {

		Texture::Texture()			
			:
			image()
		{
			glGenTextures(1, &this->texID);
		}

		Texture::Texture(Texture&& t)
			:
			image(t.image)

		{
			glGenTextures(1, &this->texID);
			this->BufferTexture();
		}

		Texture::Texture(const Texture& t)
			:
			image(t.image)
		{
			glGenTextures(1, &this->texID);

			glBindTexture(GL_TEXTURE_2D, this->texID);
			this->BufferTexture();
		}





		Texture::Texture(const ImageData& image)
			:
			image(image)
		{
			glGenTextures(1, &this->texID);
			this->BufferTexture();
		}

		Texture::Texture(ImageData&& image)
		{
			// Moving the data
			this->image.pixels = image.pixels;
			this->image.width = image.width;
			this->image.height = image.height;
			this->image.BPP = image.BPP;

			image.pixels = nullptr;

			glGenTextures(1, &this->texID);
			this->BufferTexture();
		}

		Texture::Texture(const unsigned int& texID)
			: 
			image(),
			texID(texID)
		{}

		Texture::~Texture()
		{
			glDeleteTextures(1, &this->texID);
		}







		void Texture::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D , this->texID);
		}

		void Texture::Unbind()	const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture::Reset(const ImageData& image)
		{
			this->image = image;
			this->BufferTexture();
		}

		void Texture::Reset(ImageData&& image)
		{
			this->image = std::move(image);
			this->BufferTexture();
		}

	}
}