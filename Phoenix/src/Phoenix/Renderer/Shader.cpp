#include "pch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Phoenix
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& name)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PH_CORE_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc, name);
		default:
			PH_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Shader* Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PH_CORE_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(path);
		default:
			PH_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Shader* Shader::Create(const std::string& path, const std::string& name)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PH_CORE_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(path, name);
		default:
			PH_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		if(shaders.find(shader->GetName()) == shaders.end()) 
		{
			shaders[shader->GetName()] = shader;
			return;
		}
		PH_CORE_WARN("Shader '{0}' already exists in library", shader->GetName());
	}

	void ShaderLibrary::Load(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& name)
	{
		if (shaders.find(name) == shaders.end())
		{
			Ref<Shader> ref;
			ref.reset(Shader::Create(vertexSrc, fragmentSrc, name));
			shaders[name] = ref;
			return;
		}
		PH_CORE_WARN("Shader '{0}' already exists in library", name);
	}

	void ShaderLibrary::Load(const std::string& path, const std::string& name)
	{
		if (shaders.find(name) == shaders.end())
		{
			Ref<Shader> ref;
			ref.reset(Shader::Create(path, name));
			shaders[name] = ref;
			return;
		}
		PH_CORE_WARN("Shader '{0}' already exists in library", name);
	}

	void ShaderLibrary::Load(const std::string& path)
	{
		namespace fs = std::filesystem;

		std::string name = fs::path(path).stem().string();
		Load(path, name);
	}

	const Ref<Shader>& ShaderLibrary::Get(const std::string& name) const
	{
		auto iter = shaders.find(name);
		PH_CORE_ASSERT(iter != shaders.end(), "Shader '{0}' doesn't exist in library", name);
		return iter->second;
	}
}