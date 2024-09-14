#pragma once

#include "glm/glm.hpp"

namespace Phoenix
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& name);
		static Shader* Create(const std::string& path, const std::string& name);
		static Shader* Create(const std::string& path);
	};


	class ShaderLibrary 
	{
	public:
		void Add(const Ref<Shader>& shader);

		void Load(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& name);
		void Load(const std::string& path, const std::string& name);
		void Load(const std::string& path);

		const Ref<Shader>& Get(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}