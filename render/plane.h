//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_PLANE_H
#define DEMO_RAY_TRACER_PLANE_H

#include "primitive.h"

class Plane: public Primitive {
public:
    Plane(const Vec3 &center, const Vec3 &normal, float width, float height, shared_ptr<Material> mat) : Primitive(mat), m_center(center), m_normal(normal), m_width(width), m_height(height) {};

    bool boundingBox(Aabb &outputBox) const override {
        float halfWidth = m_width * 0.5;
        float halfHeight = m_height * 0.5;
        outputBox = Aabb(
                m_center - Vec3(halfWidth, halfHeight, 0),
                m_center + Vec3(halfWidth, halfHeight, 0)
        );
        return true;
    }

    bool hit(const Ray &r, float t0, float t1, RayHitResult& res) override {
        float denominator = -m_normal.dot(r.direction());

        if (denominator > 1e-6) {
            Vec3 p = m_center - r.origin();
            float t = p.dot(m_normal.inverse()) / denominator;
            Point3 hitP = r.evaluate(t);
            // have not handle plane's rotation
            if (t > t0 && t < t1 && (hitP.x() - m_center.x()) < m_width && (hitP.y() - m_center.y()) < m_height) {
                res.t = t;
                res.point = r.evaluate(t);
                res.setFaceNormal(r, m_normal);
                res.matPtr = m_mat;
                return true;
            }
        }

        return false;
    }

private:
    Vec3 m_center;
    Vec3 m_normal;
    float m_width;
    float m_height;
};

#endif //DEMO_RAY_TRACER_PLANE_H
