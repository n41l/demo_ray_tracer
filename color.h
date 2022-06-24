//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_COLOR_H
#define DEMO_RAY_TRACER_COLOR_H

#include "math.h"
#include <iostream>

void write_color(std::ostream &out, Color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif //DEMO_RAY_TRACER_COLOR_H
