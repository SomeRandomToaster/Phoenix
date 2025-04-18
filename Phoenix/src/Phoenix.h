#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

#include "Phoenix/Application.h"
#include "Phoenix/Log.h"
#include "Phoenix/Layer.h"
#include "Phoenix/Input.h"

#include "Phoenix/ImGui/ImGuiLayer.h"

#include "Phoenix/Renderer/Buffer.h"
#include "Phoenix/Renderer/Camera.h"
#include "Phoenix/Renderer/OrthographicCamera.h"
#include "Phoenix/Renderer/Renderer.h"
#include "Phoenix/Renderer/RenderCommand.h"
#include "Phoenix/Renderer/Shader.h"
#include "Phoenix/Renderer/Texture.h"
#include "Phoenix/Renderer/VertexArray.h"
#include "Phoenix/Renderer/Framebuffer.h"

#include "Phoenix/Core/Timestep.h"

#include "Phoenix/OrthographicCameraController.h"

#ifdef PH_INCLUDE_MAIN
	#include "Phoenix/EntryPoint.h"
#endif // PH_INCLUDE_MAIN

