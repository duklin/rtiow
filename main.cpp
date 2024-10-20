#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main(){
    hittable_list scene;
    scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    auto aspect_ratio = 16.0 / 9.0;
    size_t image_width = 400;
    size_t samples_per_pixel = 100;
    size_t max_ray_bounces = 20;
    camera cam(aspect_ratio, image_width, samples_per_pixel, max_ray_bounces);    

    cam.render(scene);
}