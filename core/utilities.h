//
// Created by Kun Huang on 2022/7/4.
//

#ifndef DEMO_RAY_TRACER_UTILITIES_H
#define DEMO_RAY_TRACER_UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline float degreesToRadians(float degrees) {
    return degrees * pi / 180.0;
}

#endif //DEMO_RAY_TRACER_UTILITIES_H
