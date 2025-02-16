#pragma once

#include "Phoenix/Renderer/Texture.h"

namespace Phoenix
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();

		unsigned int GetWidth() const override { return width; }
		unsigned int GetHeight() const override { return height; }
		void Bind(unsigned int slot = 0) const override;
		virtual uint32_t GetRendererID() const override { return textureID; }
	private:
		unsigned int textureID;
		unsigned int width, height;
	};
}