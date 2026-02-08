#pragma once

#include <Models/Vehicle/StaticVehicleModel.h>

namespace ModelExamples
{
	class Sphere : public StaticVehicleModel
	{
	public:
		Sphere(float m_kg, float r_m);
	};

	class LeadBall50Cal : public Sphere
	{
	public:
		LeadBall50Cal()
			: Sphere(12e-3f, 6.35e-3f) {
		}
	};
}