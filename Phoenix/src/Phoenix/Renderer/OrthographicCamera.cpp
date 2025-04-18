#include "pch.h"
#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Phoenix
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		location = glm::vec3(0.0);
		rotation = glm::vec3(0.0);
		projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
		viewMatrix = glm::mat4(1.0f);
		projectionViewMatrix = projectionMatrix;
	}

	void OrthographicCamera::SetLocation(const glm::vec3& location)
	{
		this->location = location;
		RecalculateMatrices();
	}

	void OrthographicCamera::SetRotation(const glm::vec3& rotation)
	{
		this->rotation = rotation;
		RecalculateMatrices();
	}

	void OrthographicCamera::RecalculateMatrices()
	{
		glm::mat4 transform= glm::translate(glm::mat4(1), location);
		transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));

		

		viewMatrix = glm::inverse(transform);
		projectionViewMatrix = projectionMatrix * viewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
		RecalculateMatrices();
	}
}