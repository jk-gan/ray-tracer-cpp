//
// Created by Jun Kai Gan on 27/07/2024.
//

#pragma once

#include "vec3.h"

class ray {
public:
    ray() { }
    ray(const point3& origin, const vec3& direction)
        : _origin(origin)
        , _direction(direction) { }

    [[nodiscard]] const point3& origin() const { return _origin; }
    [[nodiscard]] const vec3& direction() const { return _direction; }

    // ray.at(t) = P(t) = A + tb, where A = origin, b = direction, t = time
    [[nodiscard]] auto at(const double t) const -> point3 { return _origin + t * _direction; }

private:
    point3 _origin;
    vec3 _direction;
};
