//
// Created by Jun Kai Gan on 30/07/2024.
//

#pragma once
#include "rtweekend.h"

class interval {
public:
    double min, max;

    interval()
        : min(+DOUBLE_INFINITY)
        , max(-DOUBLE_INFINITY) { } // Default interval is empty
    interval(double min, double max)
        : min(min)
        , max(max) { }

    [[nodiscard]] auto size() const -> double { return max - min; }
    [[nodiscard]] auto contains(double x) const -> bool { return min <= x && x <= max; }
    [[nodiscard]] auto surrounds(double x) const -> bool { return min < x && x < max; }
    [[nodiscard]] auto clamp(double x) const -> double {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+DOUBLE_INFINITY, -DOUBLE_INFINITY);
const interval interval::universe = interval(-DOUBLE_INFINITY, +DOUBLE_INFINITY);
