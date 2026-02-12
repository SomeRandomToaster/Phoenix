#pragma once

struct StaticVehicleModel
{
	double m_kg;
	double Jx_kgm2;
	double Jy_kgm2;
	double Jz_kgm2;
	double Jxz_kgm2;
	double CD_approx;
	double Aref_m2;
};