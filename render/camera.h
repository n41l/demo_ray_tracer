//
// Created by Kun Huang on 2022/7/4.
//

#ifndef DEMO_RAY_TRACER_CAMERA_H
#define DEMO_RAY_TRACER_CAMERA_H
#include "../core/core.h"
#include "ray.h"

class Camera {
public:
    Camera() {
        float aspectRatio = 16.0 / 9.0;
        float viewportHeight  = 2.0;
        float viewPortWidth = aspectRatio * viewportHeight;
        float focalLength = 1.0;

        origin = Point3(0, 0, 0);
        horizontal = Vec3(viewPortWidth, 0.0, 0.0);
        vertical = Vec3(0.0, viewportHeight, 0.0);
        lowerLeftCorner = origin - horizontal  / 2 - vertical / 2 - Vec3(0, 0, focalLength);
    }

    Ray getRay(float u, float v) {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
    }

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
};


#endif //DEMO_RAY_TRACER_CAMERA_H
