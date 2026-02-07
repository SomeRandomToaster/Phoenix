#include <Math/Common.h>

namespace Math
{
	std::vector<float> RangeArray(float start, float stop, float step)
	{
		std::vector<float> ans;
		ans.reserve(size_t(ceil((stop - start) / step)));

		float val = start;

		while (val < stop) {
			ans.push_back(val);
			val += step;
		}

		return ans;
	}
}