#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter (
            ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered
        ) const {
            return false;
        }
};

class lambertian : public material {
    public:
        lambertian(color const& albedo) : albedo(albedo) {}

        bool scatter (
            ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered
        ) const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
    
    private:
        color albedo;
};

class metal : public material {
    public:
        metal(color const& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}
    
        bool scatter(
            ray const& r_in, hit_record const& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(reflected, rec.normal) > 0);
        }

    private:
        color albedo;
        double fuzz;
};

#endif