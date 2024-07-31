//
// Created by Jun Kai Gan on 29/07/2024.
//

#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
    sphere(const point3& center, double radius, std::shared_ptr<material> material)
        : center(center)
        , radius(std::fmax(0.0, radius))
        , material(material) { }

    auto hit(const ray& ray, interval ray_t, hit_record& rec) const -> bool override {
        const vec3 oc = center - ray.origin();
        const auto a = ray.direction().length_squared();
        const auto h = dot(ray.direction(), oc);
        const auto c = oc.length_squared() - radius * radius;

        const auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.point = ray.at(rec.t);
        rec.normal = (rec.point - center) / radius;
        const vec3 outward_normal = (rec.point - center) / radius;
        rec.set_face_normal(ray, outward_normal);
        rec.material = material;

        return true;
    }

private:
    point3 center;
    double radius;
    std::shared_ptr<material> material;
};
