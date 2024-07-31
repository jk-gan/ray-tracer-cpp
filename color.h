//
// Created by Jun Kai Gan on 27/07/2024.
//

#pragma once

#include "interval.h"
#include "vec3.h"

using color = vec3;

auto write_color(std::ostream& out, const color& pixel_color) -> void {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    static const interval intensity { 0.000, 0.999 };
    int rbyte = static_cast<int>(256 * intensity.clamp(r));
    int gbyte = static_cast<int>(256 * intensity.clamp(g));
    int bbyte = static_cast<int>(256 * intensity.clamp(b));

    // Write out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
