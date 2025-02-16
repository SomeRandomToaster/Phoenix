#pragma once
#include "Phoenix/Renderer/Framebuffer.h"


namespace Phoenix 
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferProps& props);
		~OpenGLFramebuffer();

		virtual const FramebufferProps& GetFramebufferProps() const { return props; }
		virtual uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }
		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		void Create();
	private:
		FramebufferProps props;
		uint32_t rendererID, colorAttachment;
	};
}