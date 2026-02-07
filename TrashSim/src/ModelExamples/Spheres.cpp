#include <ModelExamples/Spheres.h>

#define _USE_MATH_DEFINES
#include <cmath>

namespace ModelExamples
{
	VehicleModel Sphere(float m_kg, float r_m) {
		float J_kgm2 = 0.4f * m_kg * r_m * r_m;
		
		VehicleModel model;
		model.m_kg = m_kg;
		model.Jx_kgm2 = J_kgm2;
		model.Jy_kgm2 = J_kgm2;
		model.Jz_kgm2 = J_kgm2;
		model.Jxz_kgm2 = 0;
		model.CD_approx = 0.5;
		model.Aref_m2 = float(M_PI * r_m * r_m);

		return model;
	}
}