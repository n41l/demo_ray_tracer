//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_COLOR_H
#define DEMO_RAY_TRACER_COLOR_H

#include "math_lib.h"
#include "utilities.h"
#include <iostream>

void write_color(std::ostream &out, Color pixel_color, int samplesPerPixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(255.999 * fclamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * fclamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * fclamp(b, 0.0, 0.999)) << '\n';
}

#endif //DEMO_RAY_TRACER_COLOR_H
