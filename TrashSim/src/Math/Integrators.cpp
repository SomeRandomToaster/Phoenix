#include <Math/Integrators.h>

namespace Math
{
	namespace Integrators {
		void ForwardEuler(
			std::vector<std::vector<float>>& x,
			std::function<std::vector<float>(const std::vector<float>&, float, const void*)> f,
			std::vector<float> t_s,
			float h_s,
			const void *user_data
		)
		{
			for (size_t i = 1; i < t_s.size(); i++) {
				std::vector<float> dx = f(x[i - 1], t_s[i - 1], user_data);

				size_t nx0 = x[0].size();
				for (size_t j = 0; j < nx0; j++) {
					x[i][j] = x[i - 1][j] + dx[j] * h_s;
				}
			}
		}
	}
}