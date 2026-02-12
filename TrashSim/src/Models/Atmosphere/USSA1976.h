#pragma once

#include <DataTools/Table.h>

#include <vector>
#include <string>

struct USSA1976
{
	Table table;

	static double InterpByTable(const std::vector<double>&, double h);
	USSA1976()
	: table("assets/atmosphere/ussa1976.csv") { }
};