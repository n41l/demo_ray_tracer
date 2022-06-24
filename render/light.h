//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_LIGHT_H
#define DEMO_RAY_TRACER_LIGHT_H

#include <math.h>
#include "../core/color.h"
#include "ray.h"
#include "primitive.h"

class Light {
public:
    virtual Color illuminate(const Ray &r, const RayHitResult & rHit) = 0;
};

class PointLight : public Light {
public:
    PointLight(Vec3 pos, Color intensity): m_position(pos), m_intensity(intensity) {};

    Color illuminate(const Ray &r, const RayHitResult &rHit) override {
        Vec3 hitPoint = r.evaluate(rHit.t());
        Vec3 lightDir = m_position.minus(hitPoint);
        Color E = m_intensity.scale(std::max(0.0f, rHit.normal().dot(lightDir.normalize())) / lightDir.magnitudeSquare());
        Color k = rHit.primitive()->material()->evaluate(lightDir.normalize(), r.direction().inverse().normalize(), rHit.normal());
        return Color(k.x() * E.x(), k.y() * E.y(), k.z() * E.z());
    }

private:
    Color m_intensity;
    Vec3 m_position;
};

class DirectionLight : public Light {
public:
    DirectionLight(Vec3 dir, Color intensity) : m_direction(dir), m_normalIntensity(intensity) {};

    Color illuminate(const Ray &r, const RayHitResult &rHit) override {
        Color E = m_normalIntensity.scale(std::max(0.0f, rHit.normal().dot(m_direction.inverse())));
        Color k = rHit.primitive()->material()->evaluate(m_direction.inverse(), r.direction().inverse().normalize(), rHit.normal());
        return Color(k.x() * E.x(), k.y() * E.y(), k.z() * E.z());
    }

private:
    Color m_normalIntensity;
    Vec3 m_direction;
};

#endif //DEMO_RAY_TRACER_LIGHT_H
