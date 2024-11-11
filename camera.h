#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera {
    public:
        camera(double aspect_ratio, size_t image_width, size_t spp, size_t max_ray_bounces) : aspect_ratio(aspect_ratio), image_width(image_width), samples_per_pixel(spp), max_ray_bounces(max_ray_bounces) {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);
        
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        
            pixel_samples_weight = 1.0 / samples_per_pixel;
        }

        void render (hittable const& scene){
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int y=0; y < image_height; y++){
                std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
                for (int x=0; x < image_width; x++){
                    color pixel_color(0, 0, 0);
                    for (size_t sample = 0; sample < samples_per_pixel; sample++){
                        ray r = get_ray(x, y);
                        pixel_color += ray_color(r, max_ray_bounces, scene);
                    }
                    
                    write_color(std::cout, pixel_color * pixel_samples_weight);
                }
            }
            std::clog << "\rDone.                  \n";
        }

    private:
        double aspect_ratio;
        size_t image_width;
        size_t image_height;
        point3 center = vec3(0, 0, 0);
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;
        size_t samples_per_pixel;
        double pixel_samples_weight;
        size_t max_ray_bounces;

        color ray_color(ray const& r, size_t bounces, hittable const& scene) const {
            if (bounces <= 0)
                return color(0, 0, 0);
            
            hit_record rec;

            if (scene.hit(r, interval(0.001, infinity), rec)){
                ray scattered;
                color attenuation;

                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, bounces-1, scene);

                return color(0, 0, 0);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1);
        }

        ray get_ray(int x, int y) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc 
                                + ((x + offset.x()) * pixel_delta_u) 
                                + ((y + offset.y()) * pixel_delta_v);

            auto ray_direction = pixel_sample - center;
            return ray(center, ray_direction);                    
        }

        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }
};

#endif