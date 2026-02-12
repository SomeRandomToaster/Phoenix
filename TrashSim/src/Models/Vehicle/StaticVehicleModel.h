#pragma once

#include "VehicleModel.h"

class StaticVehicleModel : public VehicleModel
{
protected:
	double m_kg;
	double Jx_kgm2;
	double Jy_kgm2;
	double Jz_kgm2;
	double Jxz_kgm2;
	double CD_approx;
	double Aref_m2;
public:
	virtual double get_m_kg() const { return m_kg; }
	virtual double get_Jx_kgm2() const { return Jx_kgm2; }
	virtual double get_Jy_kgm2() const { return Jy_kgm2; }
	virtual double get_Jz_kgm2() const { return Jz_kgm2; }
	virtual double get_Jxz_kgm2() const { return Jxz_kgm2; }
	virtual double get_CD_approx() const { return CD_approx; }
	virtual double get_Aref_m2() const { return Aref_m2; }
};