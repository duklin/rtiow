#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main(){
    hittable_list scene;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.3), 0.6);

    scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    scene.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5, material_center));
    scene.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, material_left));
    scene.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_right));

    auto aspect_ratio = 16.0 / 9.0;
    size_t image_width = 1000;
    size_t samples_per_pixel = 100;
    size_t max_ray_bounces = 50;
    camera cam(aspect_ratio, image_width, samples_per_pixel, max_ray_bounces);    

    cam.render(scene);
}