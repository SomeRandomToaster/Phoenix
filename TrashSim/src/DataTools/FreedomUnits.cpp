#include "pch.h"

#include "Units.h"

double UnitsTransform(double val, const std::string& col_name, size_t idx)
{
	std::string::size_type unit_subscript_idx = col_name.find('_');
	if (unit_subscript_idx == std::string::npos) {
		return val; // No subscript. Can't do anything.
	}
	std::string units = col_name.substr(unit_subscript_idx);

	if (units.rfind("_ftlbf") == 0) {
		return val * FT_TO_M * LBF_TO_N;
	}
	else if (units.rfind("_ft_min") == 0) {
		return val * FT_TO_M / MIN_TO_S;
	}
	else if (units.rfind("_ft_s2") == 0) {
		return val * FT_TO_M;
	}
	else if (units.rfind("_ft_s") == 0) {
		return val * FT_TO_M;
	}
	else if (units.rfind("_ft") == 0) {
		return val * FT_TO_M;
	}
	else if (units.rfind("_slug_ft3") == 0) {
		return val * SLUG_TO_KG / (FT_TO_M * FT_TO_M * FT_TO_M);
	}
	else if (units.rfind("_lbf_ft2") == 0) {
		return val * LBF_TO_N / (FT_TO_M * FT_TO_M);
	}
	else if (units.rfind("_lbf") == 0) {
		return val* LBF_TO_N;
	}
	else if (units.rfind("_nmi_h") == 0) {
		return val * NMI_TO_M / H_TO_S;
	}
	else if (units.rfind("_deg_s") == 0) {
		return val * DEG_TO_RAD;
	}
	else if (units.rfind("_deg") == 0) {
		return val * DEG_TO_RAD;
	}
	return val; // Something other 
}