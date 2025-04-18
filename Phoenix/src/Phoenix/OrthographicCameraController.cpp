#include "pch.h"
#include "OrthographicCameraController.h"

#include "Phoenix/Input.h"

namespace Phoenix
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: aspectRatio(aspectRatio), zoomLevel(1.f), camera(-zoomLevel * aspectRatio, zoomLevel * aspectRatio, -zoomLevel, zoomLevel, -zoomLevel, zoomLevel)
	{
	}


	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
        if (Input::IsKeyPressed(PH_KEY_Q))
        {
            zRotation += rotationSpeed * ts;
        }
        if (Input::IsKeyPressed(PH_KEY_E))
        {
            zRotation -= rotationSpeed * ts;
        }

        if (Input::IsKeyPressed(PH_KEY_A))
        {
            location.x -= movementSpeed * zoomLevel * ts;
        }
        if (Input::IsKeyPressed(PH_KEY_D))
        {
            location.x += movementSpeed * zoomLevel * ts;
        }
        if (Input::IsKeyPressed(PH_KEY_S))
        {
            location.y -= movementSpeed * zoomLevel * ts;
        }
        if (Input::IsKeyPressed(PH_KEY_W))
        {
            location.y += movementSpeed * zoomLevel * ts;
        }

        camera.SetRotation({ 0, 0, zRotation });
        camera.SetLocation(location);
	}


	void OrthographicCameraController::OnEvent(Event& e)
	{
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(PH_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(PH_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResize));
	}

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        zoomLevel = std::max(zoomLevel - e.GetOffsetY() * zoomSpeed, minZoomLevel);
        camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, -zoomLevel, zoomLevel);
        return false;
    }
    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
    {
        aspectRatio = float(e.GetWidth()) / float(e.GetHeight());
        camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, -zoomLevel, zoomLevel);
        return false;
    }
}