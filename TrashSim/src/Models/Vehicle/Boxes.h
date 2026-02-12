#pragma once

#include "StaticVehicleModel.h"
#include <DataTools/Units.h>

namespace ModelExamples
{
	class Box : public StaticVehicleModel
	{
	public:
		Box(double m_kg, double l_m, double w_m, double h_m);
	};

	class Brick : public Box
	{
	public:
		Brick()
			: Box(5 * LB_TO_KG, 8 * IN_TO_M, 4 * IN_TO_M, 2.25 * IN_TO_M) {
		}
	};
}