#include "pch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Phoenix/Application.h"

namespace Phoenix
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui")
	{

	}
	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = glfwGetTime();
		float deltaTime = lastUpdateTime > 0 ? time - lastUpdateTime : 1.f / 60.f;
		lastUpdateTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnWindowResizeEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseScrolledEvent));
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		/*
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;

		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;

		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;

		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;

		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		*/
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		
		io.KeyAlt = event.GetKeyCode() == PH_KEY_LEFT_ALT || event.GetKeyCode() == PH_KEY_RIGHT_ALT;
		io.KeyCtrl = event.GetKeyCode() == PH_KEY_LEFT_CONTROL || event.GetKeyCode() == PH_KEY_RIGHT_CONTROL;
		io.KeyShift = event.GetKeyCode() == PH_KEY_LEFT_SHIFT || event.GetKeyCode() == PH_KEY_RIGHT_SHIFT;
		io.KeySuper = event.GetKeyCode() == PH_KEY_LEFT_SUPER || event.GetKeyCode() == PH_KEY_RIGHT_SUPER;
		io.AddKeyEvent(PhoenixKeyToImGui(event.GetKeyCode()), 1);
		
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		

		io.KeyAlt = !(event.GetKeyCode() == PH_KEY_LEFT_ALT || event.GetKeyCode() == PH_KEY_RIGHT_ALT);
		io.KeyCtrl = !(event.GetKeyCode() == PH_KEY_LEFT_CONTROL || event.GetKeyCode() == PH_KEY_RIGHT_CONTROL);
		io.KeyShift = !(event.GetKeyCode() == PH_KEY_LEFT_SHIFT || event.GetKeyCode() == PH_KEY_RIGHT_SHIFT);
		io.KeySuper = !(event.GetKeyCode() == PH_KEY_LEFT_SUPER || event.GetKeyCode() == PH_KEY_RIGHT_SUPER);

		io.AddKeyEvent(PhoenixKeyToImGui(event.GetKeyCode()), 0);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter((unsigned short)event.GetKeyCode());

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(event.GetMouseX(), event.GetMouseY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(event.GetOffsetX(), event.GetOffsetY());

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(event.GetMouseButton(), 1);

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(event.GetMouseButton(), 0);

		return false;
	}

	ImGuiKey ImGuiLayer::PhoenixKeyToImGui(unsigned int keycode)
	{
		switch (keycode)
		{
		case PH_KEY_TAB: return ImGuiKey_Tab; 
		case PH_KEY_LEFT: return ImGuiKey_LeftArrow; 
		case PH_KEY_RIGHT: return ImGuiKey_RightArrow; 
		case PH_KEY_UP: return ImGuiKey_UpArrow; 
		case PH_KEY_DOWN: return ImGuiKey_DownArrow; 
		case PH_KEY_PAGE_UP: return ImGuiKey_PageUp; 
		case PH_KEY_PAGE_DOWN: return ImGuiKey_PageDown; 
		case PH_KEY_HOME: return ImGuiKey_Home; 
		case PH_KEY_END: return ImGuiKey_End; 
		case PH_KEY_INSERT: return ImGuiKey_Insert; 
		case PH_KEY_DELETE: return ImGuiKey_Delete; 
		case PH_KEY_BACKSPACE: return ImGuiKey_Backspace; 
		case PH_KEY_SPACE: return ImGuiKey_Space; 
		case PH_KEY_ENTER: return ImGuiKey_Enter; 
		case PH_KEY_ESCAPE: return ImGuiKey_Escape; 
		case PH_KEY_APOSTROPHE: return ImGuiKey_Apostrophe; 
		case PH_KEY_COMMA: return ImGuiKey_Comma; 
		case PH_KEY_MINUS: return ImGuiKey_Minus; 
		case PH_KEY_PERIOD: return ImGuiKey_Period; 
		case PH_KEY_SLASH: return ImGuiKey_Slash; 
		case PH_KEY_SEMICOLON: return ImGuiKey_Semicolon; 
		case PH_KEY_EQUAL: return ImGuiKey_Equal; 
		case PH_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket; 
		case PH_KEY_BACKSLASH: return ImGuiKey_Backslash; 
		case PH_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket; 
		case PH_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent; 
		case PH_KEY_CAPS_LOCK: return ImGuiKey_CapsLock; 
		case PH_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock; 
		case PH_KEY_NUM_LOCK: return ImGuiKey_NumLock; 
		case PH_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen; 
		case PH_KEY_PAUSE: return ImGuiKey_Pause; 
		case PH_KEY_KP_0: return ImGuiKey_Keypad0; 
		case PH_KEY_KP_1: return ImGuiKey_Keypad1; 
		case PH_KEY_KP_2: return ImGuiKey_Keypad2; 
		case PH_KEY_KP_3: return ImGuiKey_Keypad3; 
		case PH_KEY_KP_4: return ImGuiKey_Keypad4; 
		case PH_KEY_KP_5: return ImGuiKey_Keypad5; 
		case PH_KEY_KP_6: return ImGuiKey_Keypad6; 
		case PH_KEY_KP_7: return ImGuiKey_Keypad7; 
		case PH_KEY_KP_8: return ImGuiKey_Keypad8; 
		case PH_KEY_KP_9: return ImGuiKey_Keypad9; 
		case PH_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal; 
		case PH_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide; 
		case PH_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply; 
		case PH_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract; 
		case PH_KEY_KP_ADD: return ImGuiKey_KeypadAdd; 
		case PH_KEY_KP_ENTER: return ImGuiKey_KeypadEnter; 
		case PH_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual; 
		case PH_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift; 
		case PH_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl; 
		case PH_KEY_LEFT_ALT: return ImGuiKey_LeftAlt; 
		case PH_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper; 
		case PH_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift; 
		case PH_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl; 
		case PH_KEY_RIGHT_ALT: return ImGuiKey_RightAlt; 
		case PH_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper; 
		case PH_KEY_MENU: return ImGuiKey_Menu; 
		case PH_KEY_0: return ImGuiKey_0; 
		case PH_KEY_1: return ImGuiKey_1; 
		case PH_KEY_2: return ImGuiKey_2; 
		case PH_KEY_3: return ImGuiKey_3; 
		case PH_KEY_4: return ImGuiKey_4; 
		case PH_KEY_5: return ImGuiKey_5; 
		case PH_KEY_6: return ImGuiKey_6; 
		case PH_KEY_7: return ImGuiKey_7; 
		case PH_KEY_8: return ImGuiKey_8; 
		case PH_KEY_9: return ImGuiKey_9; 
		case PH_KEY_A: return ImGuiKey_A; 
		case PH_KEY_B: return ImGuiKey_B; 
		case PH_KEY_C: return ImGuiKey_C; 
		case PH_KEY_D: return ImGuiKey_D; 
		case PH_KEY_E: return ImGuiKey_E; 
		case PH_KEY_F: return ImGuiKey_F; 
		case PH_KEY_G: return ImGuiKey_G; 
		case PH_KEY_H: return ImGuiKey_H; 
		case PH_KEY_I: return ImGuiKey_I; 
		case PH_KEY_J: return ImGuiKey_J; 
		case PH_KEY_K: return ImGuiKey_K; 
		case PH_KEY_L: return ImGuiKey_L; 
		case PH_KEY_M: return ImGuiKey_M; 
		case PH_KEY_N: return ImGuiKey_N; 
		case PH_KEY_O: return ImGuiKey_O; 
		case PH_KEY_P: return ImGuiKey_P; 
		case PH_KEY_Q: return ImGuiKey_Q; 
		case PH_KEY_R: return ImGuiKey_R; 
		case PH_KEY_S: return ImGuiKey_S; 
		case PH_KEY_T: return ImGuiKey_T; 
		case PH_KEY_U: return ImGuiKey_U; 
		case PH_KEY_V: return ImGuiKey_V; 
		case PH_KEY_W: return ImGuiKey_W; 
		case PH_KEY_X: return ImGuiKey_X; 
		case PH_KEY_Y: return ImGuiKey_Y; 
		case PH_KEY_Z: return ImGuiKey_Z; 
		case PH_KEY_F1: return ImGuiKey_F1; 
		case PH_KEY_F2: return ImGuiKey_F2; 
		case PH_KEY_F3: return ImGuiKey_F3; 
		case PH_KEY_F4: return ImGuiKey_F4; 
		case PH_KEY_F5: return ImGuiKey_F5; 
		case PH_KEY_F6: return ImGuiKey_F6; 
		case PH_KEY_F7: return ImGuiKey_F7; 
		case PH_KEY_F8: return ImGuiKey_F8; 
		case PH_KEY_F9: return ImGuiKey_F9; 
		case PH_KEY_F10: return ImGuiKey_F10; 
		case PH_KEY_F11: return ImGuiKey_F11; 
		case PH_KEY_F12: return ImGuiKey_F12; 
		default: return ImGuiKey_None;
		}
	}
}