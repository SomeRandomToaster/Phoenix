#include <Math/Integrators.h>

namespace Math
{
	namespace Integrators {
		void ForwardEuler(
			std::vector<std::vector<double>>& x,
			std::function<std::vector<double>(const std::vector<double>&, double, const void*)> f,
			std::vector<double> t_s,
			double h_s,
			const void *user_data
		)
		{
			for (size_t i = 1; i < t_s.size(); i++) {
				std::vector<double> dx = f(x[i - 1], t_s[i - 1], user_data);

				size_t nx0 = x[0].size();
				for (size_t j = 0; j < nx0; j++) {
					x[i][j] = x[i - 1][j] + dx[j] * h_s;
				}
			}
		}

		void Bashforth(
			std::vector<std::vector<double>>& x,
			std::function<std::vector<double>(const std::vector<double>&, double, const void*)> f,
			std::vector<double> t_s,
			double h_s,
			const void* user_data
		)
		{
			// First step
			size_t nx0 = x[0].size();
			std::vector<double> dx = f(x[0], t_s[0], user_data);
			for (size_t j = 0; j < nx0; j++) {
				x[1][j] = x[0][j] + dx[j] * h_s;
			}
			std::vector<double> dx_prev = dx;

			for (size_t i = 2; i < t_s.size(); i++) {
				dx = f(x[i - 1], t_s[i - 1], user_data);

				size_t nx0 = x[0].size();
				for (size_t j = 0; j < nx0; j++) {
					if (i == 1) {
						x[i][j] = x[i - 1][j] + dx[j] * h_s;
					}
					else {

					}
					x[i][j] = x[i - 1][j] + 1.5f * dx[j] * h_s - 0.5f * dx_prev[j] * h_s;
				}

				dx_prev = dx;
			}
		}
	}
}