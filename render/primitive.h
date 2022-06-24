//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_PRIMITIVE_H
#define DEMO_RAY_TRACER_PRIMITIVE_H

#include "ray.h"
#include "material.h"

struct RayHitResult;

class Primitive {
public:
    Primitive(Material * mat): m_mat(mat){};

    Material* material() const {
        return m_mat;
    };
    virtual RayHitResult intersection(const Ray &r, float t0, float t1) = 0;

protected:
    Material *m_mat;
};

class RayHitResult {

public:
    RayHitResult(Primitive *p, float t, const Vec3 &n): m_p(p), m_t(t), m_n(n) {};
    static RayHitResult NotHit(Primitive *p) {
        return RayHitResult(p, std::numeric_limits<float>::max(), Vec3(0, 0, 0));
    }

    Primitive* primitive() const {
        return m_p;
    }


    float t() const {
        return m_t;
    }

    Vec3 normal() const {
        return m_n;
    }

private:
    Primitive *m_p;
    float m_t;
    Vec3 m_n;
};

#endif //DEMO_RAY_TRACER_PRIMITIVE_H
