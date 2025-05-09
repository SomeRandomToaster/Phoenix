#pragma once


namespace Phoenix
{
	struct FramebufferProps
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		static Ref<Framebuffer> Create(const FramebufferProps& props);


		virtual const FramebufferProps& GetFramebufferProps() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}