#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

auto main() -> int {
    hittable_list world;

    auto ground_material = std::make_shared<lambertian>(color { 0.5, 0.5, 0.5 });
    world.add(std::make_shared<sphere>(point3 { 0.0, -1000.0, 0.0 }, 1000.0, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center { a + 0.9 * random_double(), 0.2, b + 0.9 * random_double() };

            if ((center - point3 { 4.0, 0.2, 0.0 }).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0.0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3 { 0.0, 1.0, 0.0 }, 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color { 0.4, 0.2, 0.1 });
    world.add(std::make_shared<sphere>(point3 { -4.0, 1.0, 0.0 }, 1.0, material2));

    auto material3 = std::make_shared<metal>(color { 0.7, 0.6, 0.5 }, 0.0);
    world.add(std::make_shared<sphere>(point3 { 4.0, 1.0, 0.0 }, 1.0, material3));

    camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1200;
    camera.samples_per_pixel = 500;
    camera.max_depth = 50;

    camera.vfov = 20.0;
    camera.look_from = point3 { 13.0, 2.0, 3.0 };
    camera.look_at = point3 { 0.0, 0.0, 0.0 };
    camera.vup = vec3 { 0.0, 1.0, 0.0 };

    camera.defocus_angle = 0.6;
    camera.focus_distance = 10.0;

    camera.render(world);
}
