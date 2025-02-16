#include "pch.h"
#include <glm/mat4x4.hpp>

#include "AppLayer.h"



void AppLayer::DrawSettingsWindow()
{
    ImGui::Begin("Settings");

    static const char* items[] =
    {
        "Monochrome",
        "Chess board",
        "Stripes",
        "Gradient"
    };
    ImGui::Combo("Pattern", &selectedPattern, items, 4);
    switch (selectedPattern)
    {
    case Monochrome:
        ImGui::Text("Select color");
        ImGui::RadioButton("Color 1", &selectedColor, 0); ImGui::SameLine();
        ImGui::RadioButton("Color 2", &selectedColor, 1);
        break;
    case Stripes:
    case Gradient:
        ImGui::Checkbox("Change direction", &patternDirection);
        break;
    default:
        break;
    }
    ImGui::Text("Colors");
    ImGui::ColorPicker3("Color1", glm::value_ptr(color1));
    ImGui::ColorPicker3("Color2", glm::value_ptr(color2));

    ImGui::End();
}


void AppLayer::DrawViewportWindow()
{
    ImGui::Begin("Viewport");



    uint32_t id = viewportFramebuffer->GetColorAttachmentRendererID();
    ImGui::Image((void*)id, ImVec2(viewportResolutionX, viewportResolutionY));
    ImGui::End();
}


void AppLayer::DrawMenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            if (ImGui::MenuItem("Exit")) {
                Phoenix::Application::Get().Close();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}


void AppLayer::SetupDockspace()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    bool open = true;
    bool* p_open = &open;
    ImGui::Begin("Fluid Viewport", p_open, window_flags);

    ImGui::PopStyleVar();

    ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    
}


void AppLayer::OnUpdate(Phoenix::Timestep ts)
{
    if (Phoenix::Input::IsKeyPressed(PH_KEY_A))
    {
        zRotation += cameraRotationSpeed * ts;
    }
    if (Phoenix::Input::IsKeyPressed(PH_KEY_D))
    {
        zRotation -= cameraRotationSpeed * ts;
    }

    if (Phoenix::Input::IsKeyPressed(PH_KEY_LEFT))
    {
        cameraLocation.x -= cameraMovementSpeed * ts;
    }
    if (Phoenix::Input::IsKeyPressed(PH_KEY_RIGHT))
    {
        cameraLocation.x += cameraMovementSpeed * ts;
    }
    if (Phoenix::Input::IsKeyPressed(PH_KEY_DOWN))
    {
        cameraLocation.y -= cameraMovementSpeed * ts;
    }
    if (Phoenix::Input::IsKeyPressed(PH_KEY_UP))
    {
        cameraLocation.y += cameraMovementSpeed * ts;
    }

    camera->SetRotation({ 0, 0, zRotation });
    camera->SetLocation(cameraLocation);

    viewportFramebuffer->Bind();
    Phoenix::RenderCommand::ClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
    Phoenix::Renderer::BeginScene(camera);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            glm::mat4 squareTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
            squareTransform = glm::translate(squareTransform, glm::vec3(2.2f * i, 2.2f * j, 0));
            flatColorShader->Bind();
            switch (selectedPattern)
            {
            case Monochrome:
                if (selectedColor)
                    std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", color2);
                else
                    std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", color1);
                break;
            case Chessboard:
                std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", (i + j) % 2 ? color1 : color2);
                break;
            case Stripes:
                if (patternDirection)
                    std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", j % 2 ? color1 : color2);
                else
                    std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", i % 2 ? color1 : color2);
                break;
            case Gradient:
                float t;
                if (patternDirection)
                    t = j / 10.0f;
                else
                    t = i / 10.0f;
                std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", t * color1 + (1 - t) * color2);
                break;
            }
            //std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat3("u_Color", (i + j) % 2 ? color1 : color2);
            Phoenix::Renderer::Submit(flatColorShader, squareVA, squareTransform);
        }
    }

    Phoenix::Renderer::EndScene();
    viewportFramebuffer->Unbind();
}

