#pragma once

#include <Phoenix.h>

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


	std::vector<std::vector<float>> vars_to_plot;

	std::vector<float> t_s;
	std::vector<std::vector<float>> plot_y;
	int customRGBMap;

	std::vector <float> alpha_deg;
	std::vector <float> beta_deg;
	std::vector <float> mach_number;

	void SetStyle();
public:
	void OnAttach() override;
	void OnImGuiRender() override;
	void OnDetach() override;
};