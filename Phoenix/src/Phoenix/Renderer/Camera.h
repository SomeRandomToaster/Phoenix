#pragma once

#include "glm/glm.hpp"

namespace Phoenix
{
	class Camera
	{
	public:
		virtual void SetLocation(const glm::vec3& location) = 0;
		virtual const glm::vec3& GetLocation() const = 0;

		virtual void SetRotation(const glm::vec3& location) = 0;
		virtual const glm::vec3& GetRotation() const = 0;

		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetProjectionViewMatrix() const = 0;

	};
}