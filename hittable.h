#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class material;

class hit_record {
    public:
        point3 p;
        double t;
        bool front_face;
        vec3 normal;
        shared_ptr<material> mat;

        void set_face_normal(ray const& r, vec3 const& outward_normal){
            // Sets the hit record normal vector
            // NOTE: `outward_normal` is assumed to be unit vector

            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }

};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(ray const& r, interval ray_t, hit_record& rec) const = 0;
};

#endif