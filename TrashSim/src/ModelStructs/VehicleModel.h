#pragma once

struct VehicleModel
{
	float m_kg;
	float Jx_kgm2;
	float Jy_kgm2;
	float Jz_kgm2;
	float Jxz_kgm2;
	float CD_approx;
	float Aref_m2;
};