//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_RAY_H
#define DEMO_RAY_TRACER_RAY_H

#include "math.h"
class Ray {
public:
    Ray(const Vec3& o, const Vec3& d): m_origin(o), m_direction(d) {};
    Vec3 origin() const { return m_origin; }
    Vec3 direction() const { return m_direction; }

    Vec3 evaluate(float t) const {
        return m_origin.add(m_direction.scale(t));
    }

private:
    Vec3 m_origin, m_direction;
};

#endif //DEMO_RAY_TRACER_RAY_H
