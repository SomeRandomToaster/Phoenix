#include "pch.h"

#include "USSA1976.h"
#include <Math/Common.h>

#include <cstdio>
#include <array>

double USSA1976::InterpByTable(const std::vector<double>& table, double h)
{
    if (h < 0) {
        return table[0];
    }
    if (h > 50e3) {
        return table[table.size() - 1];
    }
    
    std::array<std::array<double, 4>, 3> segments = {{ // Altitude bounds, step and base index
        {0, 11e3, 50, 0},
        {11e3, 32e3, 100, 221},
        {32e3, 50e3, 200, 431}
    }};

    double t = 0;
    size_t l_idx = 0;
    size_t r_idx = 1;
    for (const auto& seg : segments) {
        double lowest_alt = seg[0];
        double highest_alt = seg[1];

        if (h >= lowest_alt && h <= highest_alt) {
            double alt_step = seg[2];
            size_t base_idx = size_t(seg[3]);
            l_idx = size_t(floor((h - lowest_alt) / alt_step + base_idx));
            r_idx = l_idx + 1;
            double l_idx_alt = (l_idx - base_idx) * alt_step + lowest_alt;
            t = (h - l_idx_alt) / alt_step;
            break;
        }
    }
    return Math::Lerp(table[l_idx], table[r_idx], t);
}