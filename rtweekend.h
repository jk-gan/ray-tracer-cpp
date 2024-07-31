//
// Created by Jun Kai Gan on 29/07/2024.
//

#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// Constants
const double DOUBLE_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility functions
inline auto degrees_to_radians(double degrees) -> double { return degrees * PI / 180.0; }
inline auto random_double() -> double {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline auto random_double(double min, double max) -> double { return min + (max - min) * random_double(); }

// Common Headers
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"
