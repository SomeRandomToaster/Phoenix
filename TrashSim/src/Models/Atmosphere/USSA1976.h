#pragma once

#include <vector>
#include <string>

struct USSA1976
{
	std::vector<float> rho_kgpm3_table;
	std::vector<float> cs_mps_table;

	static float InterpByTable(const std::vector<float>&, float h);
	USSA1976();
};