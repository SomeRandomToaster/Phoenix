#include "pch.h"

#include "USSA1976.h"

#include <cstdio>
#include <array>

float USSA1976::InterpByTable(const std::vector<float>& table, float h)
{
    if (h < 0) {
        return table[0];
    }
    if (h > 50e3) {
        return table[table.size() - 1];
    }
    
    std::array<std::array<float, 4>, 3> segments = {{ // Altitude bounds, step and base index
        {0, 11e3, 50, 0},
        {11e3, 32e3, 100, 221},
        {32e3, 50e3, 200, 431}
    }};

    float t = 0;
    size_t l_idx = 0;
    size_t r_idx = 0;
    for (auto seg : segments) {
        float lowest_alt = seg[0];
        float highest_alt = seg[1];

        if (h >= lowest_alt && h <= highest_alt) {
            float alt_step = seg[2];
            size_t base_idx = size_t(seg[3]);
            l_idx = size_t(floor((h - lowest_alt) / alt_step + base_idx));
            r_idx = size_t(ceil((h - lowest_alt) / alt_step + base_idx));
            float l_idx_alt = (l_idx - base_idx) * alt_step + lowest_alt;
            t = (h - l_idx_alt) / alt_step;
            break;
        }
    }
    return table[l_idx] * t + table[r_idx] * (1 - t);
}


USSA1976::USSA1976()
{
	FILE* csv = fopen("res/ussa1976.csv", "r");
	float rho, cs;
	while (fscanf(csv, "%f, %f\n", &rho, &cs) == 2) {
		rho_kgpm3_table.push_back(rho);
		cs_mps_table.push_back(cs);
	}
}