#pragma once

#include <Models/Vehicle/StaticVehicleModel.h>
#include <DataTools/Units.h>

namespace ModelExamples
{
	class Sphere : public StaticVehicleModel
	{
	public:
		Sphere(double m_kg, double r_m);
	};

	class LeadBall50Cal : public Sphere
	{
	public:
		LeadBall50Cal()
			: Sphere(12e-3f, 6.35e-3f) {
		}
	};

	class BowlingBall : public Sphere
	{
	public:
		BowlingBall()
			: Sphere(7.25f, 0.217f) {
		}
	};

	class Blueberry : public Sphere
	{
	public:
		Blueberry()
			: Sphere(0.75e-3f, 11e-3f) {
		}
	};

	class CannonBall : public Sphere
	{
	public:
		CannonBall()
			: Sphere(1.f * SLUG_TO_KG, 3.f * IN_TO_M) {
		}
	};
}