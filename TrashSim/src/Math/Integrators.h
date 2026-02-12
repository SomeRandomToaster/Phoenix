#pragma once

#include <vector>
#include <functional>

namespace Math {
	namespace Integrators
	{
		void ForwardEuler(
			std::vector<std::vector<double>>& x,
			std::function<std::vector<double>(const std::vector<double>&, double, const void*)> f,
			std::vector<double> t_s,
			double h_s,
			const void* user_data
		);

		void Bashforth(
			std::vector<std::vector<double>>& x,
			std::function<std::vector<double>(const std::vector<double>&, double, const void*)> f,
			std::vector<double> t_s,
			double h_s,
			const void* user_data
		);
	}
}