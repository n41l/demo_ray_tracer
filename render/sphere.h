//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_SPHERE_H
#define DEMO_RAY_TRACER_SPHERE_H

#include <algorithm>
#include "primitive.h"

class Sphere : public Primitive {
public:
    Sphere(const Vec3 &center, float radius, shared_ptr<Material> material)
            : Primitive(material), m_center(center), m_radius(radius) {};

    bool boundingBox(Aabb &outputBox) const override {
        outputBox = Aabb(
                m_center - Vec3(m_radius, m_radius, m_radius),
                m_center + Vec3(m_radius, m_radius, m_radius)
        );
        return true;
    }
    bool hit(const Ray &r, float t0, float t1, RayHitResult& res) override {
        res.primitive = this;
        float A = r.direction().dot(r.direction());
        Vec3 sCenterToROrigin = r.origin() - m_center;
        float B = r.direction().dot(sCenterToROrigin);
        float C = sCenterToROrigin.dot(sCenterToROrigin) - m_radius * m_radius;

        float discriminant = B * B - A * C;

        if (discriminant >= 0) {
            float p = 1 / A;
            float p1= sqrt(discriminant);
            float t = (-B - p1) * p;
            if (t > t0 && t < t1) {
                Vec3 hitPoint = r.evaluate(t);
                Vec3 n = (hitPoint - m_center) * 1/m_radius;
                res.t = t;
                res.point = hitPoint;
                res.matPtr = m_mat;
                res.setFaceNormal(r, n);
                getSphereUV(n, res.u, res.v);
                return true;
            }
        }
        return false;
    }

private:
    static void getSphereUV(const Point3& point, float& u, float& v) {
        float theta = acos(-point.y());
        float phi = atan2(-point.z(), point.x()) + pi;
        u = phi / (2 * pi);
        v = theta / pi;
    }

private:
    Vec3 m_center;
    float m_radius;
};

#endif //DEMO_RAY_TRACER_SPHERE_H
