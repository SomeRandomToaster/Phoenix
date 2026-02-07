#pragma once

#include <Phoenix.h>

class MainLayer : public Phoenix::Layer
{
	size_t row_count = 2;
	size_t col_count = 4;
	std::vector<size_t> var_indices = { 
		0, 1, 2, 9,
		3, 4, 5, 10
	};
	std::vector<std::string> x_labels = {
		"Time [s]", "Time [s]", "Time [s]", "Time [s]",
		"Time [s]", "Time [s]", "Time [s]", "Time [s]"
	};
	std::vector<std::string> y_labels = {
		"u [m/s]", "v [m/s]", "w [m/s]", "phi [r]",
		"p [r/s]", "q [r/s]", "r [r/s]", "theta [r]",
	};


	std::vector<std::vector<float>> vars_to_plot;

	std::vector<float> t_s;
	std::vector<std::vector<float>> plot_y;
	int customRGBMap;

	void SetStyle();
public:
	void OnAttach() override;
	void OnImGuiRender() override;
	void OnDetach() override;
};