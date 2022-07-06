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

    shared_ptr<Material> material() {
        return m_mat;
    }

    virtual bool hit(const Ray &r, float t0, float t1, RayHitResult& res) = 0;
    virtual bool boundingBox(Aabb& outputBox) const = 0;

protected:
    shared_ptr<Material> m_mat;
};

class Translate : public Primitive {
public:
    Translate(shared_ptr<Primitive> p, const Vec3& displacement) : Primitive(p->material()), m_p(p), m_offset(displacement) {}

    bool hit(const Ray &r, float t0, float t1, RayHitResult &res) override;

    bool boundingBox(Aabb &outputBox) const override;

private:
    shared_ptr<Primitive> m_p;
    Vec3 m_offset;
};

bool Translate::hit(const Ray &r, float t0, float t1, RayHitResult &res) {
    Ray translatedRay(r.origin() - m_offset, r.direction());
    if (!m_p->hit(translatedRay, t0, t1, res))
        return false;
    res.point += m_offset;
    res.setFaceNormal(translatedRay, res.normal);
    return true;
}

bool Translate::boundingBox(Aabb &outputBox) const {
    if (!m_p->boundingBox(outputBox))
        return false;

    outputBox = Aabb(
            outputBox.min() + m_offset,
            outputBox.max() + m_offset
            );
    return true;
}

class RotateY : public Primitive {
public:
    RotateY(shared_ptr<Primitive> p, float angle);
    bool hit(const Ray &r, float t0, float t1, RayHitResult &res) override;
    bool boundingBox(Aabb &outputBox) const override {
        outputBox = m_box;
        return m_hasBox;
    }

private:
    shared_ptr<Primitive> m_p;
    float m_sinTheta;
    float m_cosTheta;
    bool m_hasBox;
    Aabb m_box;
};

RotateY::RotateY(shared_ptr<Primitive> p, float angle) : Primitive(p->material()), m_p(p) {
    float radians = degreesToRadians(angle);
    m_sinTheta = sin(radians);
    m_cosTheta = cos(radians);
    m_hasBox = m_p->boundingBox(m_box);
    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * m_box.max().x() + (1 - i) * m_box.min().x();
                auto y = j * m_box.max().y() + (1 - j) * m_box.min().y();
                auto z = k * m_box.max().z() + (1 - k) * m_box.min().z();

                auto newX = m_cosTheta * x + m_sinTheta * z;
                auto newZ = -m_sinTheta * x + m_cosTheta * z;

                Vec3 tester(newX, y, newZ);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    m_box = Aabb(min, max);
}

bool RotateY::hit(const Ray &r, float t0, float t1, RayHitResult &res) {
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = m_cosTheta*r.origin()[0] - m_sinTheta*r.origin()[2];
    origin[2] = m_sinTheta*r.origin()[0] + m_cosTheta*r.origin()[2];

    direction[0] = m_cosTheta*r.direction()[0] - m_sinTheta*r.direction()[2];
    direction[2] = m_sinTheta*r.direction()[0] + m_cosTheta*r.direction()[2];

    Ray rotated_r(origin, direction);

    if (!m_p->hit(rotated_r, t0, t1, res))
        return false;

    auto p = res.point;
    auto normal = res.normal;

    p[0] =  m_cosTheta*res.point[0] + m_sinTheta*res.point[2];
    p[2] = -m_sinTheta*res.point[0] + m_cosTheta*res.point[2];

    normal[0] =  m_cosTheta*res.normal[0] + m_sinTheta*res.normal[2];
    normal[2] = -m_sinTheta*res.normal[0] + m_cosTheta*res.normal[2];

    res.point = p;
    res.setFaceNormal(rotated_r, normal);

    return true;
}

#endif //DEMO_RAY_TRACER_PRIMITIVE_H
