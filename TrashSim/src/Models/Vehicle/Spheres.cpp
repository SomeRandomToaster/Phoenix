#include "Spheres.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace ModelExamples
{
	Sphere::Sphere(float m_kg, float r_m) {
		float J_kgm2 = 0.4f * m_kg * r_m * r_m;
		
		this->m_kg = m_kg;
		this->Jx_kgm2 = J_kgm2;
		this->Jy_kgm2 = J_kgm2;
		this->Jz_kgm2 = J_kgm2;
		this->Jxz_kgm2 = 0;
		this->CD_approx = 0.5;
		this->Aref_m2 = float(M_PI * r_m * r_m);
	}
}