//
// Created by Jun Kai Gan on 31/07/2024.
//

#pragma once

#include "rtweekend.h"

class hit_record;

class material {
public:
    virtual ~material() = default;
    virtual auto scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool {
        return false;
    }
};

class lambertian : public material {
public:
    lambertian(const color& albedo)
        : albedo(albedo) { }

    auto scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // catch degenerate scatter directions
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray { rec.point, scatter_direction };
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class metal : public material {
public:
    metal(const color& albedo, double fuzz)
        : albedo(albedo)
        , fuzz(fuzz < 1.0 ? fuzz : 1.0) { }

    auto scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
        vec3 reflected = reflect(ray_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = ray { rec.point, reflected };
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0.0);
    }

private:
    color albedo;
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double refraction_index)
        : refraction_index(refraction_index) { }

    auto scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
        attenuation = color { 1.0, 1.0, 1.0 };
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction = unit_vector(ray_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > random_double()) {
            direction = reflect(unit_direction, rec.normal);
        } else {
            direction = refract(unit_direction, rec.normal, ri);
        }

        scattered = ray { rec.point, direction };

        return true;
    }

private:
    // refractive index in vacuum or air, or the ratio of the material's refractive index over the refractive index of
    // the enclosing media
    double refraction_index;

    static auto reflectance(double cosine, double refraction_index) -> double {
        // use Schlick's approximation for reflectance
        auto r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
    }
};
