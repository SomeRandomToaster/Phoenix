#pragma once

#include <vector>

namespace Math
{
	std::vector<float> RangeArray(float start, float stop, float step);

	inline float Lerp(float a, float b, float t) { return a * (1 - t) + b * t; }
}