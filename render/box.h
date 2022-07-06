//
// Created by Kun Huang on 2022/7/6.
//

#ifndef DEMO_RAY_TRACER_BOX_H
#define DEMO_RAY_TRACER_BOX_H
#include "../core/core.h"
#include "aarect.h"
#include "scene.h"

class Box : public Primitive {
public:
    Box() : Primitive(nullptr) {}
    Box(const Point3& p_min, const Point3& p_max, shared_ptr<Material> mat);

    bool hit(const Ray &r, float t0, float t1, RayHitResult &res) override;

    bool boundingBox(Aabb &outputBox) const override {
        outputBox = Aabb(m_box_min, m_box_max);
        return true;
    }

private:
    Point3 m_box_min;
    Point3 m_box_max;
    Scene m_sides;
};

Box::Box(const Point3 &p_min, const Point3 &p_max, shared_ptr<Material> mat) : Primitive(mat) {
    m_box_min = p_min;
    m_box_max = p_max;


    m_sides.addPrimitive(make_shared<xy_rect>(m_box_min.x(), m_box_max.x(), m_box_min.y(), m_box_max.y(), m_box_max.z(), mat));
    m_sides.addPrimitive(make_shared<xy_rect>(m_box_min.x(), m_box_max.x(), m_box_min.y(), m_box_max.y(), m_box_min.z(), mat));

    m_sides.addPrimitive(make_shared<xz_rect>(m_box_min.x(), m_box_max.x(), m_box_min.z(), m_box_max.z(), m_box_max.y(), mat));
    m_sides.addPrimitive(make_shared<xz_rect>(m_box_min.x(), m_box_max.x(), m_box_min.z(), m_box_max.z(), m_box_min.y(), mat));

    m_sides.addPrimitive(make_shared<yz_rect>(m_box_min.y(), m_box_max.y(), m_box_min.z(), m_box_max.z(), m_box_max.x(), mat));
    m_sides.addPrimitive(make_shared<yz_rect>(m_box_min.y(), m_box_max.y(), m_box_min.z(), m_box_max.z(), m_box_min.x(), mat));
}

bool Box::hit(const Ray &r, float t0, float t1, RayHitResult &res) {
    return m_sides.hit(r, t0, t1, res);
}

#endif //DEMO_RAY_TRACER_BOX_H
