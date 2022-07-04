//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_PLANE_H
#define DEMO_RAY_TRACER_PLANE_H

#include "primitive.h"

class Plane: public Primitive {
public:
    Plane(const Vec3 &center, const Vec3 &normal, shared_ptr<Material> mat): Primitive(mat), m_center(center), m_normal(normal) {};

    RayHitResult intersection(const Ray &r, float t0, float t1) override {
        RayHitResult res;
        res.primitive = this;
        float denominator = -m_normal.dot(r.direction());

        if (denominator > 1e-6) {
            Vec3 p = m_center - r.origin();
            float t = p.dot(m_normal.inverse()) / denominator;

            if (t > t0 && t < t1) {
                res.t = t;
                res.point = r.evaluate(t);
                res.setFaceNormal(r, m_normal);
                res.matPtr = m_mat;
                return res;
            }
        }

        res.t = std::numeric_limits<float>::max();
        res.isFrontFace = false;
        return res;
    }

private:
    Vec3 m_center;
    Vec3 m_normal;
};

#endif //DEMO_RAY_TRACER_PLANE_H
