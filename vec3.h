#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    public:
        double e[3];

        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(vec3 const& v){
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];
            return *this;
        }

        vec3& operator*=(double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t){
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, vec3 const& v){
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(vec3 const& u, vec3 const& v){
    return vec3(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}

inline vec3 operator-(vec3 const& u, vec3 const& v){
    return vec3(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}

inline vec3 operator*(vec3 const& u, vec3 const& v){
    return vec3(u[0]*v[0], u[1]*v[1], u[2]*v[2]);
}

inline vec3 operator*(double t, vec3 const& u){
    return vec3(t*u[0], t*u[1], t*u[2]);
}

inline vec3 operator*(vec3 const& u, double t){
    return t * u;
}

inline vec3 operator/(vec3 const& u, double t){
    return (1/t) * u;
}

inline double dot(vec3 const& u, vec3 const& v){
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

inline vec3 cross(vec3 const& u, vec3 const& v){
    return vec3(u[1]*v[2] - u[2]*v[1],
                u[2]*v[0] - u[0]*v[2],
                u[0]*v[1] - u[1]*v[0]);
}

inline vec3 unit_vector(vec3 const& u){
    return u / u.length();
}

#endif