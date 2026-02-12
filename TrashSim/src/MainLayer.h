#pragma once

#include <Phoenix.h>
#include <DataTools/Table.h>

class MainLayer : public Phoenix::Layer
{
	size_t win0_row_count = 2;
	size_t win0_col_count = 4;
	size_t win1_row_count = 3;
	size_t win1_col_count = 3;
	std::vector<size_t> var_indices = { 
		0, 1, 2, 9,
		3, 4, 5, 10,

		6, 7, 8
	};
	std::vector<std::string> x_labels = {
		"Time [s]", "Time [s]", "Time [s]", "Time [s]",
		"Time [s]", "Time [s]", "Time [s]", "Time [s]"
	};
	std::vector<std::string> y_labels = {
		"u [m/s]", "v [m/s]", "w [m/s]", "phi [r]",
		"p [r/s]", "q [r/s]", "r [r/s]", "theta [r]"
	};

	bool verification_mode = true;
	bool verification_plot_pos = true;
	bool verification_plot_attitude = true;
	bool verification_plot_angular_rates = true;
	bool verification_plot_velocity = true;

	std::vector<ImColor> plot_colors = {
		{ 1.f, 1.f, 0.f, 1.f }, // Main window plots
		{ 1.f, 0.f, 1.f, 1.f }, // Aux window upper plots
		{ 0.02f, 0.73f, 0.87f, 1.f }, // Aux window lower plots
		{ 1.f, 0.f, 0.f, 1.f } // Verification data plots
	};

	std::vector<std::vector<double>> vars_to_plot;

	std::vector<double> t_s;
	std::vector<std::vector<double>> plot_y;

	std::vector <double> alpha_deg;
	std::vector <double> beta_deg;
	std::vector <double> mach_number;
	
	Table verification_data;

	void SetStyle();
	void LoadVerificationData(const std::string& filename);
public:
	void OnAttach() override;
	void OnImGuiRender() override;
	void OnDetach() override;
};