//
// Created by Jun Kai Gan on 29/07/2024.
//

#pragma once

#include "rtweekend.h"

class material;

class hit_record {
public:
    point3 point;
    vec3 normal;
    std::shared_ptr<material> material;
    double t;
    bool front_face;

    auto set_face_normal(const ray& ray, const vec3& outward_normal) -> void {
        // Sets the hit record normal vector
        // NOTE: the parameter `outward_normal` is assumed to have unit length

        front_face = dot(ray.direction(), outward_normal) < 0.0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual auto hit(const ray& ray, interval ray_t, hit_record& rec) const -> bool = 0;
};
