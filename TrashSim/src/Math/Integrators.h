#pragma once

#include <vector>
#include <functional>

namespace Math {
	namespace Integrators
	{
		void ForwardEuler(
			std::vector<std::vector<float>>& x,
			std::function<std::vector<float>(const std::vector<float>&, float, const void*)> f,
			std::vector<float> t_s,
			float h_s,
			const void* user_data
		);
	}
}