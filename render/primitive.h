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

struct RayHitResult {
    Primitive *primitive;
    float t;
    Vec3 normal;
    bool isFrontFace;

    inline void setFaceNormal(const Ray& r, const Vec3 &n) {
        isFrontFace = r.direction().dot(n) < 0;
        normal = isFrontFace ? n : n.inverse();
    }
};

#endif //DEMO_RAY_TRACER_PRIMITIVE_H
