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


	std::vector<std::vector<double>> vars_to_plot;

	std::vector<double> t_s;
	std::vector<std::vector<double>> plot_y;

	std::vector <double> alpha_deg;
	std::vector <double> beta_deg;
	std::vector <double> mach_number;
	
	bool verification_mode = true;
	Table verification_data;

	void SetStyle();
	void LoadVerificationData();
public:
	void OnAttach() override;
	void OnImGuiRender() override;
	void OnDetach() override;
};