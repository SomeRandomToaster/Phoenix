#pragma once

#include "Phoenix/Renderer/OrthographicCamera.h"
#include "Phoenix/Core/Timestep.h"
#include "Phoenix/Events/MouseEvent.h"
#include "Phoenix/Events/ApplicationEvent.h"

namespace Phoenix
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio);
		
		const OrthographicCamera& GetCamera() const { return camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		float aspectRatio;

		float zoomLevel;
		float minZoomLevel = 0.2f;
		float zoomSpeed = 0.1f;

		float zRotation = 0;
		float rotationSpeed = 180.f;

		float movementSpeed = 5.0f;
		glm::vec3 location = { 0, 0, 0 };

		OrthographicCamera camera;
	};
}