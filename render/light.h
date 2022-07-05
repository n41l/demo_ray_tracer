//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_LIGHT_H
#define DEMO_RAY_TRACER_LIGHT_H

#include "../core/color.h"
#include "ray.h"
#include "primitive.h"
#include "scene.h"

class Light {
public:
    virtual Color illuminate(const Ray &r, const RayHitResult & rHit, Scene &scene) = 0;
};

#endif //DEMO_RAY_TRACER_LIGHT_H
