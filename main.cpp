#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

auto main() -> int {
    hittable_list world;

    world.add(std::make_shared<sphere>(point3 { 0.0, 0.0, -1.0 }, 0.5));
    world.add(std::make_shared<sphere>(point3 { 0.0, -100.5, -1.0 }, 100.0));

    camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.render(world);

    return 0;
}
