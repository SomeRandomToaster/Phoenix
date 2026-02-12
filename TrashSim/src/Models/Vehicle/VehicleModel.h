#pragma once

class VehicleModel
{
public:
	virtual double get_m_kg() const = 0;
	virtual double get_Jx_kgm2() const = 0;
	virtual double get_Jy_kgm2() const = 0;
	virtual double get_Jz_kgm2() const = 0;
	virtual double get_Jxz_kgm2() const = 0;
	virtual double get_CD_approx() const = 0;
	virtual double get_Aref_m2() const = 0;
};