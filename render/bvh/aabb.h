//
// Created by Kun Huang on 2022/7/5.
//

#ifndef DEMO_RAY_TRACER_AABB_H
#define DEMO_RAY_TRACER_AABB_H
#include "../../core/core.h"
#include "../ray.h"

class Aabb {
public:
    Aabb() {}
    Aabb(const Point3& min, const Point3& max) : m_min(min), m_max(max) {}

    Point3 min() const { return m_min; }
    Point3 max() const { return m_max; }

    bool hit(const Ray& ray, float tMin, float tMax) const {
        for (int a = 0; a < 3; a++) {
            auto invD = 1.0f / ray.direction()[a];
            auto t0 = (min()[a] - ray.origin()[a]) * invD;
            auto t1 = (max()[a] - ray.origin()[a]) * invD;
            if (invD < 0.0f)
                std::swap(t0, t1);
            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;
            if (tMax <= tMin)
                return false;
        }
        return true;
    }

private:
    Point3 m_min;
    Point3 m_max;
};

Aabb surroundingBox(Aabb box0, Aabb box1) {
    Point3 min(fmin(box0.min().x(), box1.min().x()),
                 fmin(box0.min().y(), box1.min().y()),
                 fmin(box0.min().z(), box1.min().z()));

    Point3 max(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));

    return Aabb(min, max);
}

#endif //DEMO_RAY_TRACER_AABB_H
