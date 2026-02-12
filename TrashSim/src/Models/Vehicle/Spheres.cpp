#include "Spheres.h"

#include <cmath>

namespace ModelExamples
{
	Sphere::Sphere(double m_kg, double r_m) {
		double J_kgm2 = 0.4 * m_kg * r_m * r_m;
		
		this->m_kg = m_kg;
		this->Jx_kgm2 = J_kgm2;
		this->Jy_kgm2 = J_kgm2;
		this->Jz_kgm2 = J_kgm2;
		this->Jxz_kgm2 = 0;
		this->CD_approx = 0.5;
		this->Aref_m2 = double(M_PI * r_m * r_m);
	}
}