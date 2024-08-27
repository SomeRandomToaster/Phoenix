#include "pch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include "glad/glad.h"

namespace Phoenix
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PH_CORE_ASSERT(image, "Couldn't load image!");

		this->width = width;
		this->height = height;
		
		unsigned int internalFormat = 0, dataFormat = 0;

		if (channels == 3)
		{
			dataFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else if (channels == 4)
		{
			dataFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		PH_CORE_ASSERT(dataFormat && internalFormat, "Unsupported texture format!");

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glTextureStorage2D(textureID, 1, internalFormat, this->width, this->height);

		glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(textureID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, image);

		stbi_image_free(image);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &textureID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, textureID);
	}
}