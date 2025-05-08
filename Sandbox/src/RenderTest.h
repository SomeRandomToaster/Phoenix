#pragma once

#include <Phoenix.h>

class RenderTest : public Phoenix::Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Phoenix::Timestep ts) override;
	void OnEvent(Phoenix::Event& e) override;
	void OnImGuiRender() override;
private:
	Phoenix::OrthographicCameraController cameraController{ 1280.f / 720.f };

	Ref<Phoenix::VertexArray> squareVA;
	Ref<Phoenix::Shader> flatColorShader;
	Ref<Phoenix::Texture2D> texture;
	
	glm::vec4 squareColor = { 0.5, 0.7, 0.2, 1.0 };
};