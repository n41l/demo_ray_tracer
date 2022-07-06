//
// Created by Kun Huang on 2022/7/6.
//

#ifndef DEMO_RAY_TRACER_AARECT_H
#define DEMO_RAY_TRACER_AARECT_H
#include "../core/core.h"
#include "primitive.h"

class xy_rect : public Primitive {
public:
    xy_rect() : Primitive(nullptr) {}
    xy_rect(float x_min, float x_max, float y_min, float y_max, float k, shared_ptr<Material> mat)
        : m_x_min(x_min), m_x_max(x_max), m_y_min(y_min), m_y_max(y_max), m_k(k), Primitive(mat) {};

    bool hit(const Ray &r, float t0, float t1, RayHitResult &res) override;
    bool boundingBox(Aabb &outputBox) const override {
        outputBox = Aabb(Point3(m_x_min, m_y_min, m_k - 0.0001), Point3(m_x_max, m_y_max, m_k + 0.0001));
        return true;
    }

private:
    float m_x_min, m_x_max, m_y_min, m_y_max, m_k;
};

bool xy_rect::hit(const Ray &r, float t0, float t1, RayHitResult &res) {
    auto t = (m_k-r.origin().z()) / r.direction().z();
    if (t < t0 || t > t1)
        return false;
    auto x = r.origin().x() + t*r.direction().x();
    auto y = r.origin().y() + t*r.direction().y();
    if (x < m_x_min || x > m_x_max || y < m_y_min || y > m_y_max)
        return false;
    res.u = (x-m_x_min)/(m_x_max-m_x_min);
    res.v = (y-m_y_min)/(m_y_max-m_y_min);
    res.t = t;
    auto outward_normal = Vec3(0, 0, 1);
    res.setFaceNormal(r, outward_normal);
    res.matPtr = m_mat;
    res.point = r.evaluate(t);
    return true;
}

class xz_rect : public Primitive {
public:
    xz_rect() : Primitive(nullptr) {}

    xz_rect(double x_min, double x_max, double z_min, double z_max, double k,
            shared_ptr<Material> mat)
            : m_x_min(x_min), m_x_max(x_max), m_z_min(z_min), m_z_max(z_max), m_k(k), Primitive(mat) {};

    bool hit(const Ray &r, float t0, float t1, RayHitResult &res) override;

    bool boundingBox(Aabb &outputBox) const override {
        outputBox = Aabb(Point3(m_x_min,m_k-0.0001,m_z_min), Point3(m_x_max, m_k+0.0001, m_z_max));
        return true;
    }

public:
    float m_x_min, m_x_max, m_z_min, m_z_max, m_k;
};

bool xz_rect::hit(const Ray &r, float t0, float t1, RayHitResult &res) {
    auto t = (m_k-r.origin().y()) / r.direction().y();
    if (t < t0 || t > t1)
        return false;
    auto x = r.origin().x() + t*r.direction().x();
    auto z = r.origin().z() + t*r.direction().z();
    if (x < m_x_min || x > m_x_max || z < m_z_min || z > m_z_max)
        return false;
    res.u = (x-m_x_min)/(m_x_max-m_x_min);
    res.v = (z-m_z_min)/(m_z_max-m_z_min);
    res.t = t;
    auto outward_normal = Vec3(0, 1, 0);
    res.setFaceNormal(r, outward_normal);
    res.matPtr = m_mat;
    res.point = r.evaluate(t);
    return true;
}

class yz_rect : public Primitive {
public:
    yz_rect() : Primitive(nullptr) {}

    yz_rect(double y_min, double y_max, double z_min, double z_max, double k,
            shared_ptr<Material> mat)
            : m_y_min(y_min), m_y_max(y_max), m_z_min(z_min), m_z_max(z_max), m_k(k), Primitive(mat) {};

    bool hit(const Ray &r, float t0, float t1, RayHitResult &res) override;

    bool boundingBox(Aabb &outputBox) const override {
        outputBox = Aabb(Point3(m_k-0.0001, m_y_min, m_z_min), Point3(m_k+0.0001, m_y_max, m_z_max));
        return true;
    }

public:
    float m_y_min, m_y_max, m_z_min, m_z_max, m_k;
};

bool yz_rect::hit(const Ray &r, float t0, float t1, RayHitResult &res) {
    float t = (m_k-r.origin().x()) / r.direction().x();
    if (t < t0 || t > t1)
        return false;
    float y = r.origin().y() + t*r.direction().y();
    float z = r.origin().z() + t*r.direction().z();
    if (y < m_y_min || y > m_y_max || z < m_z_min || z > m_z_max)
        return false;
    res.u = (y-m_y_min)/(m_y_max-m_y_min);
    res.v = (z-m_z_min)/(m_z_max-m_z_min);
    res.t = t;
    auto outward_normal = Vec3(1, 0, 0);
    res.setFaceNormal(r, outward_normal);
    res.matPtr = m_mat;
    res.point = r.evaluate(t);
    return true;
}

#endif //DEMO_RAY_TRACER_AARECT_H
