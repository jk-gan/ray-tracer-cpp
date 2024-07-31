//
// Created by Jun Kai Gan on 30/07/2024.
//

#pragma once

#include "rtweekend.h"

#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0; // ratio of image width over height
    int image_width = 100; // rendered image width in pixel count
    int samples_per_pixel = 10; // count of random samples for each pixel
    int max_depth = 10; // maximum number of ray bounces into scene

    auto render(const hittable& world) -> void {
        initialize();

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color { 0.0, 0.0, 0.0 };
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int image_height = 0; // rendered image height
    double pixel_samples_scale; // color scale factor for a sum of pixel samples
    point3 center; // camera center
    point3 pixel00_loc; // location of pixel 0, 0
    vec3 pixel_delta_u; // offset to pixel to the right
    vec3 pixel_delta_v; // offset to pixel to the bottom

    auto initialize() -> void {
        // Calculate the image height, and ensure that it's at least 1
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        constexpr auto focal_length = 1.0;
        constexpr auto viewport_height = 2.0;
        const auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        center = point3 { 0.0, 0.0, 0.0 };

        // Calculate the vector across the horizontal (vector u) and down the vertical viewport edges (vector v)
        const auto viewport_u = vec3 { viewport_width, 0.0, 0.0 };
        const auto viewport_v = vec3 { 0.0, -viewport_height, 0.0 };

        // Calculate the horizontal (delta u) and vertical (delta v) delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left corner of the viewport
        const auto viewport_upper_left = center - vec3 { 0.0, 0.0, focal_length } - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    [[nodiscard]] auto get_ray(int i, int j) const -> ray {
        // Construct a camera ray originating from the origin and directed at randomly
        // sampled point around the pixel location (i, j)
        const auto offset = sample_square();
        const auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        const auto ray_origin = center;
        const auto ray_direction = pixel_sample - ray_origin;

        return ray { ray_origin, ray_direction };
    }

    [[nodiscard]] auto sample_square() const -> vec3 {
        // Returns the vector to a random point in the [-0.5, -0.5] - [+0.5, +0.5] unit square
        return vec3 { random_double() - 0.5, random_double() - 0.5, 0.0 };
    }

    auto ray_color(const ray& r, int depth, const hittable& world) -> color {
        // if we've exceeded the ray bounce limit, no more light is gathered
        if (depth <= 0)
            return color { 0.0, 0.0, 0.0 };

        hit_record rec;

        if (world.hit(r, interval { 0.001, DOUBLE_INFINITY }, rec)) {
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray { rec.point, direction }, depth - 1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color { 1.0, 1.0, 1.0 } + a * color { 0.5, 0.7, 1.0 };
    }
};
