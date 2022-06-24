//
// Created by Kun Huang on 2022/6/24.
//

#include "ray.h"

#ifndef DEMO_RAY_TRACER_PRIMITIVE_H
#define DEMO_RAY_TRACER_PRIMITIVE_H

struct RayHitResult;

class Primitive {
public:
    virtual Color color() const = 0;
    virtual RayHitResult intersection(const Ray &r, float t0, float t1) = 0;
};

class RayHitResult {

public:
    RayHitResult(Primitive *p, const Ray &r, float t, const Vec3 &n): m_p(p), m_r(r), m_t(t), m_n(n) {};
    static RayHitResult NotHit(Primitive *p, const Ray &r) {
        return RayHitResult(p, r, std::numeric_limits<float>::max(), Vec3(0, 0, 0));
    }

    Primitive* primitive() {
        return m_p;
    }

    Ray ray() {
        return m_r;
    }

    float t() const {
        return m_t;
    }

    Vec3 normal() const {
        return m_n;
    }

private:
    Primitive *m_p;
    Ray m_r;
    float m_t;
    Vec3 m_n;
};

#endif //DEMO_RAY_TRACER_PRIMITIVE_H
