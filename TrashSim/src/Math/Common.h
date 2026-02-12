#pragma once

#include <vector>

namespace Math
{
	std::vector<double> RangeArray(double start, double stop, double step);

	inline double Lerp(double a, double b, double t) { return a * (1 - t) + b * t; }
}