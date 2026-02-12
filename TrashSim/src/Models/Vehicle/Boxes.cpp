#include "pch.h"

#include "Boxes.h"

namespace ModelExamples
{
	Box::Box(double m_kg, double l_m, double w_m, double h_m)
	{
		this->m_kg = m_kg;
		this->Jx_kgm2 = (w_m * w_m + h_m * h_m) * m_kg / 12.f;
		this->Jy_kgm2 = (l_m * l_m + h_m * h_m) * m_kg / 12.f;
		this->Jz_kgm2 = (l_m * l_m + w_m * w_m) * m_kg / 12.f;
		this->Jxz_kgm2 = 0;
		this->CD_approx = 1.05;
		this->Aref_m2 = l_m * l_m + w_m * w_m;
	}
}