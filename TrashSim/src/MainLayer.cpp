#include "pch.h"

#include <MainLayer.h>
#include <Models/Vehicle/Spheres.h>
#include <Models/Atmosphere/USSA1976.h>
#include <Math/Common.h>
#include <Math/Integrators.h>
#include <Equations/FlatEarth.h>

#include <implot/implot.h>

#include <cmath>
#include <vector>

void MainLayer::OnAttach()
{
	// Vehicle model
	StaticVehicleModel* vmod = new ModelExamples::LeadBall50Cal();
	USSA1976* amod = new USSA1976();

	// Initial values
	float u0_b_mps = 0.0f; // X-component of initial velocity
	float v0_b_mps = 0.0f; // Y-component of initial velocity
	float w0_b_mps = 0.0f; // Z-component of initial velocity
	float p0_b_rps = 0.0f; // Initial roll rate
	float q0_b_rps = 0.0f; // Initial pitch rate
	float r0_b_rps = 0.0f; // Initial yaw rate
	float x0_n_m = 0.0f; // Initial X coordinate
	float y0_n_m = 0.0f; // Initial Y coordinate
	float z0_n_m = -10000.0f; // Initial Z coordinate
	float phi0_n_r = 0.0f; // Initial roll 
	float theta0_n_r = float(-M_PI_2); // Initial pitch
	float psi0_n_r = 0.0f; // Initial yaw

	// Time bounds
	float t0_s = 0.0f;
	float tf_s = 100.0f;
	float h_s = 0.005f;

	// Integration
	std::vector<float> x0 = {
		u0_b_mps,
		v0_b_mps,
		w0_b_mps,
		p0_b_rps,
		q0_b_rps,
		r0_b_rps,
		x0_n_m,
		y0_n_m,
		z0_n_m,
		phi0_n_r,
		theta0_n_r,
		psi0_n_r
	};
	size_t nx0 = x0.size();

	t_s = Math::RangeArray(t0_s, tf_s + h_s, h_s);
	size_t nt_s = t_s.size();
	std::vector<std::vector<float>> x(nt_s, std::vector<float>(nx0));
	x[0] = x0;

	ModelSet models = {
		vmod,
		amod
	};

	Math::Integrators::ForwardEuler(x, Equations::FlatEarth, t_s, h_s, &models);

	// Output
	PH_TRACE("Terminal velocity is {:.3f} m/s\n", x[nt_s - 1][0]);

	// Plot data preparation
	vars_to_plot = { var_indices.size(), std::vector<float>(nt_s) };
	for (size_t i = 0; i < var_indices.size(); i++) {
		size_t idx = var_indices[i];
		
		for (size_t j = 0; j < nt_s; j++) {
			vars_to_plot[i][j] = x[j][idx];
		}
	}

	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImPlot::CreateContext();

	SetStyle();
}


void MainLayer::OnImGuiRender()
{
	ImGui::DockSpaceOverViewport();
	
	//// Plotting
	ImGui::Begin("Plots");
	

	if (ImPlot::BeginSubplots("", row_count, col_count, {-1, -1}))
	{
		for (int row = 0; row < row_count; row++)
		{
			for (int column = 0; column < col_count; column++)
			{
				size_t idx = row * col_count + column;

				if (ImPlot::BeginPlot("")) {
					ImPlot::SetNextLineStyle({ 1, 1, 0, 1 });
					ImPlot::SetupAxes(x_labels[idx].c_str(), y_labels[idx].c_str());
					ImPlot::PlotLine("", t_s.data(), vars_to_plot[idx].data(), t_s.size());
					ImPlot::EndPlot();
				}
			}
		}
	}
	ImPlot::EndSubplots();
	

	ImGui::End();
}


void MainLayer::OnDetach()
{
	ImPlot::DestroyContext();
}


void MainLayer::SetStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.04f, 0.04f, 0.04f, 0.99f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.51f, 0.51f, 0.80f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.03f, 0.03f, 0.04f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.17f, 0.17f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.60f, 0.10f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.60f, 0.10f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.43f, 0.90f, 0.11f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.21f, 0.22f, 0.23f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.51f, 0.51f, 0.80f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.55f, 0.55f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.51f, 0.51f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.03f, 0.03f, 0.03f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.16f, 0.16f, 0.16f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.23f, 0.23f, 0.24f, 0.80f);
	colors[ImGuiCol_Tab] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.99f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.14f, 0.87f, 0.05f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.99f, 0.60f, 0.10f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.23f, 0.78f, 0.02f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.46f, 0.47f, 0.46f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.78f, 0.69f, 0.69f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}