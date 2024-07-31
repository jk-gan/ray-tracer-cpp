//
// Created by Jun Kai Gan on 29/07/2024.
//

#pragma once

#include "rtweekend.h"

#include "hittable.h"

#include <vector>

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list() {};
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    auto clear() -> void { objects.clear(); }
    auto add(std::shared_ptr<hittable> object) -> void { objects.push_back(object); }
    auto hit(const ray& ray, interval ray_t, hit_record& rec) const -> bool override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object: objects) {
            if (object->hit(ray, interval { ray_t.min, closest_so_far }, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};
