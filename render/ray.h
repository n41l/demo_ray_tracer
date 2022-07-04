//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_RAY_H
#define DEMO_RAY_TRACER_RAY_H
#include "../core/core.h"


class Primitive;
class Material;

class Ray {
public:
    Ray() {}
    Ray(const Vec3& o, const Vec3& d): m_origin(o), m_direction(d) {};
    Vec3 origin() const { return m_origin; }
    Vec3 direction() const { return m_direction; }

    Vec3 evaluate(float t) const {
        return m_origin + m_direction * t;
    }

private:
    Vec3 m_origin, m_direction;
};

struct RayHitResult {
public:
    Primitive *primitive;
    shared_ptr<Material> matPtr;
    float t;
    Point3 point;
    Vec3 normal;
    bool isFrontFace;

    inline void setFaceNormal(const Ray& r, const Vec3 &n) {
        isFrontFace = r.direction().dot(n) < 0;
        normal = isFrontFace ? n : n.inverse();
    }
};


#endif //DEMO_RAY_TRACER_RAY_H
