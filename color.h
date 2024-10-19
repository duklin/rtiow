#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, color const& pixel_color){
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif