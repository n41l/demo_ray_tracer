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
        float A = r.direction().dot(r.direction());
        Vec3 sCenterToROrigin = r.origin().minus(m_center);
        float B = r.direction().dot(sCenterToROrigin);
        float C = sCenterToROrigin.dot(sCenterToROrigin) - m_radius * m_radius;

        float discriminant = B * B - A * C;

        if (discriminant > 0) {
            float p = 1 / A;
            float p1= sqrt(discriminant);
            float t1 = (-B + p1) * p;
            float t2 = (-B - p1) * p;

            float minT = std::min(t1, t2);
            float maxT = std::max(t1, t2);

            if (minT > t0 && minT < t1) {
                return calculate(r, minT);
            } else {
                if (maxT > t0 && maxT < t1) {
                    return calculate(r, maxT);
                }
            }
        } else if (discriminant == 0) {
            float t = -B / A;
            if (t > t0 && t < t1) {
                return calculate(r, t);
            }
        }

        return RayHitResult::NotHit((Primitive *) this);
    }

private:
    RayHitResult calculate(const Ray &r, float t) const {
        Vec3 p = r.evaluate(t);
        Vec3 n = p.minus(m_center).scale(1/m_radius);
        return RayHitResult((Primitive *) this, t, n);
    }

private:
    Vec3 m_center;
    float m_radius;
};

#endif //DEMO_RAY_TRACER_SPHERE_H
