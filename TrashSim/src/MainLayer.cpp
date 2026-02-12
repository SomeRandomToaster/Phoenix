#include "pch.h"

#include <MainLayer.h>
#include <Models/Vehicle/Spheres.h>
#include <Models/Vehicle/Boxes.h>
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
	StaticVehicleModel* vmod = new ModelExamples::Brick();
	// Atmosphere model
	USSA1976* amod = new USSA1976();
	// Verification data load
	if (verification_mode) {
		LoadVerificationData("assets/verification/Atmos_02_sim_01.csv");
	}

	// Initial values
	double u0_b_mps = 0.0f; // X-component of initial velocity
	double v0_b_mps = 0.0f; // Y-component of initial velocity
	double w0_b_mps = 0.0f; // Z-component of initial velocity
	double p0_b_rps = 10.0 * DEG_TO_RAD; // Initial roll rate
	double q0_b_rps = 20.0 * DEG_TO_RAD; // Initial pitch rate
	double r0_b_rps = 30.0 * DEG_TO_RAD; // Initial yaw rate
	double x0_n_m = 0.0f; // Initial X coordinate
	double y0_n_m = 0.0f; // Initial Y coordinate
	double z0_n_m = -30000.0f * FT_TO_M; // Initial Z coordinate
	double phi0_n_r = 0.0f; // Initial roll 
	double theta0_n_r = 0.0f; // Initial pitch
	double psi0_n_r = 0.0f; // Initial yaw

	// Time bounds
	double t0_s = 0.0f;
	double tf_s = 30.0f;
	double h_s = 0.01f;

	// Integration
	std::vector<double> x0 = {
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
	std::vector<std::vector<double>> x(nt_s, std::vector<double>(nx0));
	x[0] = x0;

	ModelSet models = {
		vmod,
		amod
	};

	Math::Integrators::Bashforth(x, Equations::FlatEarth, t_s, h_s, &models);
	
	// Post-processing
	alpha_deg = std::vector<double>(nt_s);
	beta_deg = std::vector<double>(nt_s);
	mach_number = std::vector<double>(nt_s);

	for (size_t i = 0; i < nt_s; i++) {
		double u_b_mps = x[i][0];
		double v_b_mps = x[i][1];
		double w_b_mps = x[i][2];
		double z_n_m = x[i][8];
		double h_m = -z_n_m;

		double true_airspeed_mps = sqrtf(u_b_mps * u_b_mps + v_b_mps * v_b_mps + w_b_mps * w_b_mps);
		double speed_of_sound = USSA1976::InterpByTable(amod->table["cs_mps"], h_m);

		double w_over_u = 0;
		if (u_b_mps != 0) {
			w_over_u = w_b_mps / u_b_mps;
		}

		double v_over_Vrel = 0;
		if (true_airspeed_mps != 0) {
			v_over_Vrel = v_b_mps / true_airspeed_mps;
		}

		double alpha_r = atan(w_over_u);
		double beta_r = asin(v_over_Vrel);

		alpha_deg[i] = double(alpha_r * 180.f / M_PI);
		beta_deg[i] = double(beta_r * 180.f / M_PI);
		mach_number[i] = true_airspeed_mps / speed_of_sound;
	}

	// Output
	// PH_TRACE("Terminal velocity is {:.3f} m/s\n", x[nt_s - 1][0]);

	// Plot data preparation
	vars_to_plot = { var_indices.size(), std::vector<double>(nt_s) };
	for (size_t i = 0; i < var_indices.size(); i++) {
		size_t idx = var_indices[i];
		
		for (size_t j = 0; j < nt_s; j++) {
			if (idx == 8) {
				vars_to_plot[i][j] = -x[j][idx];
			}
			else {
				vars_to_plot[i][j] = x[j][idx];
			}
			
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
	
	size_t idx = 0;
	if (ImPlot::BeginSubplots("", (int)win0_row_count, (int)win0_col_count, {-1, -1}))
	{
		for (int row = 0; row < win0_row_count; row++)
		{
			for (int column = 0; column < win0_col_count; column++)
			{

				if (ImPlot::BeginPlot("")) {

					ImPlot::SetupAxes(x_labels[idx].c_str(), y_labels[idx].c_str());

					if (verification_mode) {
						ImPlot::SetNextLineStyle(plot_colors[3]);
						switch (idx) {
						case 0:
							if (verification_plot_velocity) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["u_b_mps"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 1:
							if (verification_plot_velocity) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["v_b_mps"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 2:
							if (verification_plot_velocity) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["w_b_mps"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 3:
							if (verification_plot_attitude) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["phi_n_r"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 4:
							if (verification_plot_angular_rates) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["p_b_rps"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 5:
							if (verification_plot_angular_rates) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["q_b_rps"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 6:
							if (verification_plot_angular_rates) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["r_b_rps"].data(), (int)verification_data["t_s"].size());
							}
							break;
						case 7:
							if (verification_plot_attitude) {
								ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["theta_n_r"].data(), (int)verification_data["t_s"].size());
							}
							break;
						default:
							break;
						}
					}

					ImPlot::SetNextLineStyle(plot_colors[0]);
					ImPlot::PlotLine("", t_s.data(), vars_to_plot[idx].data(), (int)t_s.size());
					ImPlot::EndPlot();
				}
				idx++;
			}
		}
	}
	ImPlot::EndSubplots();
	ImGui::End();



	ImGui::Begin("More plots");
	if (ImPlot::BeginSubplots("1", (int)win1_row_count, (int)win1_col_count, { -1, -1 }))
	{
		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[1]);
			ImPlot::SetupAxes("Time [s]", "AoA [deg]");
			ImPlot::PlotLine("", t_s.data(), alpha_deg.data(), (int)t_s.size());
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[1]);
			ImPlot::SetupAxes("Time [s]", "AoS [deg]");
			ImPlot::PlotLine("", t_s.data(), beta_deg.data(), (int)t_s.size());
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			/*
			ImPlot::SetNextLineStyle(plot_colors[1]);
			ImPlot::SetupAxes("Time [s]", "Mach");
			ImPlot::PlotLine("", t_s.data(), mach_number.data(), (int)t_s.size());
			if (verification_mode && verification_plot_velocity) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["mach"].data(), (int)verification_data["t_s"].size());
			}
			*/

			ImPlot::SetNextLineStyle(plot_colors[1]);
			ImPlot::SetupAxes("Time [s]", "Yaw [r]");
			ImPlot::PlotLine("", t_s.data(), vars_to_plot[11].data(), (int)t_s.size());
			if (verification_mode && verification_plot_velocity) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["psi_n_r"].data(), (int)verification_data["t_s"].size());
			}

			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[2]);
			ImPlot::SetupAxes("Time [s]", "North [m]");
			ImPlot::PlotLine("", t_s.data(), vars_to_plot[8].data(), (int)t_s.size());
			if (verification_mode && verification_plot_pos) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["north_m"].data(), (int)verification_data["t_s"].size());
			}
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[2]);
			ImPlot::SetupAxes("Time [s]", "East [m]");
			ImPlot::PlotLine("", t_s.data(), vars_to_plot[9].data(), (int)t_s.size());
			if (verification_mode && verification_plot_pos) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["east_m"].data(), (int)verification_data["t_s"].size());
			}
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[2]);
			ImPlot::SetupAxes("Time [s]", "Altitude [m]");
			ImPlot::PlotLine("", t_s.data(), vars_to_plot[10].data(), (int)t_s.size());
			if (verification_mode && verification_plot_pos) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["t_s"].data(), verification_data["alt_m"].data(), (int)verification_data["t_s"].size());
			}
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[2]);
			ImPlot::SetupAxes("North [m]", "Altitude [m]");
			ImPlot::PlotLine("", vars_to_plot[8].data(), vars_to_plot[10].data(), (int)t_s.size());
			if (verification_mode && verification_plot_pos) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["north_m"].data(), verification_data["alt_m"].data(), (int)verification_data["t_s"].size());
			}
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[2]);
			ImPlot::SetupAxes("East [m]", "Altitude [m]");
			ImPlot::PlotLine("", vars_to_plot[9].data(), vars_to_plot[10].data(), (int)t_s.size());
			if (verification_mode && verification_plot_pos) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["east_m"].data(), verification_data["alt_m"].data(), (int)verification_data["t_s"].size());
			}
			ImPlot::EndPlot();
		}

		if (ImPlot::BeginPlot("")) {
			ImPlot::SetNextLineStyle(plot_colors[2]);
			ImPlot::SetupAxes("East [m]", "North [m]");
			ImPlot::PlotLine("", vars_to_plot[8].data(), vars_to_plot[9].data(), (int)t_s.size());
			if (verification_mode && verification_plot_pos) {
				ImPlot::SetNextLineStyle(plot_colors[3]);
				ImPlot::PlotLine("", verification_data["east_m"].data(), verification_data["north_m"].data(), (int)verification_data["t_s"].size());
			}
			ImPlot::EndPlot();
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

void MainLayer::LoadVerificationData(const std::string& filename)
{
	verification_data = Table(filename, UnitsTransform);

	verification_data.rename_col("time", "t_s");

	if (verification_plot_velocity) {
		verification_data.rename_col("feVelocity_ft_s_X", "u_b_mps");
		verification_data.rename_col("feVelocity_ft_s_Y", "v_b_mps");
		verification_data.rename_col("feVelocity_ft_s_Z", "w_b_mps");
	}

	if (verification_plot_attitude) {
		verification_data.rename_col("eulerAngle_deg_Roll", "phi_n_r");
		verification_data.rename_col("eulerAngle_deg_Pitch", "theta_n_r");
		verification_data.rename_col("eulerAngle_deg_Yaw", "psi_n_r");
	}

	if (verification_plot_angular_rates) {
		verification_data.rename_col("bodyAngularRateWrtEi_deg_s_Roll", "p_b_rps");
		verification_data.rename_col("bodyAngularRateWrtEi_deg_s_Pitch", "q_b_rps");
		verification_data.rename_col("bodyAngularRateWrtEi_deg_s_Yaw", "r_b_rps");
	}

	if (verification_plot_pos) {
		verification_data.rename_col("gePosition_ft_Z", "north_m");
		verification_data.rename_col("gePosition_ft_Y", "east_m");
		verification_data.rename_col("altitudeMsl_ft", "alt_m");
	}
}