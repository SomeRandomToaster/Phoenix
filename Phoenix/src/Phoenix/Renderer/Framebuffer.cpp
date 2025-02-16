#include "pch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Phoenix
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferProps& props)
	{
		Ref<Framebuffer> ref;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PH_CORE_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			ref.reset(new OpenGLFramebuffer(props));
			return ref;
		default:
			PH_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}