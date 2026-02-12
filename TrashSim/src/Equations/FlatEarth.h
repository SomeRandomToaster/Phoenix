#pragma once

#include <Models/ModelSet.h>

#include <vector>

namespace Equations
{
	std::vector<double> FlatEarth(const std::vector<double>& x, double t, const void* data);
}