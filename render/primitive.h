//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_PRIMITIVE_H
#define DEMO_RAY_TRACER_PRIMITIVE_H

#include "../core/core.h"
#include "material.h"
#include "bvh/aabb.h"

struct RayHitResult;

class Primitive {
public:
    Primitive(shared_ptr<Material> mat): m_mat(mat){};

    virtual bool hit(const Ray &r, float t0, float t1, RayHitResult& res) = 0;
    virtual bool boundingBox(Aabb& outputBox) const = 0;

protected:
    shared_ptr<Material> m_mat;
};
#endif //DEMO_RAY_TRACER_PRIMITIVE_H
