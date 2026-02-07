#pragma once

#include <ModelStructs/VehicleModel.h>

namespace ModelExamples
{
	VehicleModel Sphere(float m_kg, float r_m);

	inline VehicleModel LeadBall50Cal() {
		return Sphere(12e-3f, 6.35e-3f);
	}
}