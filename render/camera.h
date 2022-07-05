//
// Created by Kun Huang on 2022/7/4.
//

#ifndef DEMO_RAY_TRACER_CAMERA_H
#define DEMO_RAY_TRACER_CAMERA_H
#include "../core/core.h"
#include "ray.h"

class Camera {
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 upDir, float fov, float aspectRatio): m_lookFrom(lookFrom), m_lookAt(lookAt), m_upDir(upDir), m_fov(fov) {
        float theta = degreesToRadians(fov);
        float h = tan(theta / 2);
        float viewportHeight  = 2.0f * h;
        float viewPortWidth = aspectRatio * viewportHeight;

        Vec3 w = (lookFrom - lookAt).normalize();
        Vec3 u = upDir.cross(w).normalize();
        Vec3 v = w.cross(u);

        origin = lookFrom;
        horizontal = viewPortWidth * u;
        vertical = viewportHeight * v;
        lowerLeftCorner = origin - horizontal  / 2 - vertical / 2 - w;
    }

    Ray getRay(float u, float v) {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    float m_fov;
    Point3 m_lookFrom;
    Point3 m_lookAt;
    Vec3 m_upDir;
};


#endif //DEMO_RAY_TRACER_CAMERA_H
