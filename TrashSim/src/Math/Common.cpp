#include <Math/Common.h>

namespace Math
{
	std::vector<double> RangeArray(double start, double stop, double step)
	{
		std::vector<double> ans;
		ans.reserve(size_t(ceil((stop - start) / step)));

		double val = start;

		while (val < stop) {
			ans.push_back(val);
			val += step;
		}

		return ans;
	}
}