#pragma once

#include <string>
#include <cmath>

#define FT_TO_M 0.3048
#define IN_TO_M 0.0254
#define NMI_TO_M 1852

#define SLUG_TO_KG 14.593902937

#define LBF_TO_N 4.4482216153

#define MIN_TO_S 60
#define H_TO_S 3600

#define DEG_TO_RAD M_PI / 180.0

// Converts to metric
double UnitsTransform(double val, const std::string& col_name, size_t idx);