//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_PRIMITIVE_H
#define DEMO_RAY_TRACER_PRIMITIVE_H

#include "material.h"

struct RayHitResult;

class Primitive {
public:
    Primitive(shared_ptr<Material> mat): m_mat(mat){};

    shared_ptr<Material> material() const {
        return m_mat;
    };
    virtual RayHitResult intersection(const Ray &r, float t0, float t1) = 0;

protected:
    shared_ptr<Material> m_mat;
};
#endif //DEMO_RAY_TRACER_PRIMITIVE_H
