//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_SPHERE_H
#define DEMO_RAY_TRACER_SPHERE_H

#include <algorithm>
#include "primitive.h"

class Sphere : public Primitive {
public:
    Sphere(const Vec3 &center, float radius, Material *material)
            : Primitive(material), m_center(center), m_radius(radius) {};

    virtual RayHitResult intersection(const Ray &r, float t0, float t1) override {
        RayHitResult res;
        res.primitive = this;
        float A = r.direction().dot(r.direction());
        Vec3 sCenterToROrigin = r.origin().minus(m_center);
        float B = r.direction().dot(sCenterToROrigin);
        float C = sCenterToROrigin.dot(sCenterToROrigin) - m_radius * m_radius;

        float discriminant = B * B - A * C;

        if (discriminant >= 0) {
            float p = 1 / A;
            float p1= sqrt(discriminant);
            float t = (-B - p1) * p;
            if (t > t0 && t < t1) {
                Vec3 hitPoint = r.evaluate(t);
                Vec3 n = hitPoint.minus(m_center).scale(1/m_radius);
                res.t = t;
                res.setFaceNormal(r, n);
                return res;
            }
        }

        res.t = std::numeric_limits<float>::max();
        res.isFrontFace = false;
        return res;
    }

private:
    RayHitResult calculate(const Ray &r, float t) const {

    }

private:
    Vec3 m_center;
    float m_radius;
};

#endif //DEMO_RAY_TRACER_SPHERE_H
