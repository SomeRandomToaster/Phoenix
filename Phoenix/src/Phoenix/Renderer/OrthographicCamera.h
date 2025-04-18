#pragma once

#include "Camera.h"

namespace Phoenix
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);

		void SetLocation(const glm::vec3& location) override;
		const glm::vec3& GetLocation() const override { return location; }

		void SetRotation(const glm::vec3& rotation) override;
		const glm::vec3& GetRotation() const override { return rotation; }

		void SetProjection(float left, float right, float bottom, float top, float zNear, float zFar);

		const glm::mat4& GetProjectionMatrix() const override { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const override { return viewMatrix; }
		const glm::mat4& GetProjectionViewMatrix() const { return projectionViewMatrix; }
	private:
		void RecalculateMatrices();
	private:
		glm::vec3 location;
		glm::vec3 rotation;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionViewMatrix;
	};
}