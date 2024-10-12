#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}

        ray(point3 const& origin, vec3 const& direction) : orig(origin), dir(direction) {}

        point3 const& origin() const { return orig; }
        point3 const& direction() const { return dir; }

        point3 at(double t) const {
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif