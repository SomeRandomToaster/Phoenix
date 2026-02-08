#pragma once

#include <Models/ModelSet.h>

#include <vector>

namespace Equations
{
	std::vector<float> FlatEarth(const std::vector<float>& x, float t, const void* data);
}