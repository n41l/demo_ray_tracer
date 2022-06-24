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
    virtual Color illuminate(const Ray &r, const RayHitResult & rHit, Scene &scene) = 0;
};

class PointLight : public Light {
public:
    PointLight(Vec3 pos, Color intensity): m_position(pos), m_intensity(intensity) {};

    Color illuminate(const Ray &r, const RayHitResult &rHit, Scene &scene) override {
        Vec3 hitPoint = r.evaluate(rHit.t());
        Vec3 lightDir = m_position.minus(hitPoint);
        if (inShadow(hitPoint, lightDir, scene)) {
            return Color(0, 0, 0);
        } else {
            Color E = m_intensity.scale(std::max(0.0f, rHit.normal().dot(lightDir.normalize())) / lightDir.magnitudeSquare());
            Color k = rHit.primitive()->material()->evaluate(lightDir.normalize(), r.direction().inverse().normalize(), rHit.normal());
            return Color(k.x() * E.x(), k.y() * E.y(), k.z() * E.z());
        }
    }

private:
    bool inShadow(Vec3 hitP, Vec3 lightDir, Scene &scene) {
        Vec3 shadowRayDir = lightDir.normalize();
        Ray shadowRay = Ray(hitP.add(shadowRayDir.scale(0.01)), shadowRayDir);
        for (auto primitive : scene.primitives()) {
            RayHitResult res = primitive->intersection(shadowRay, 0.01, sqrt(lightDir.magnitudeSquare()));
            if (res.t() < std::numeric_limits<float>::max()) {
                return true;
            }
        }
    }

private:
    Color m_intensity;
    Vec3 m_position;
};

class DirectionLight : public Light {
public:
    DirectionLight(Vec3 dir, Color intensity) : m_direction(dir), m_normalIntensity(intensity) {};

    Color illuminate(const Ray &r, const RayHitResult &rHit, Scene &scene) override {
        Vec3 hitPoint = r.evaluate(rHit.t());
        if (inShadow(hitPoint, m_direction, scene)) {
            return Color(0, 0, 0);
        } else {
            Color E = m_normalIntensity.scale(std::max(0.0f, rHit.normal().dot(m_direction.inverse())));
            Color k = rHit.primitive()->material()->evaluate(m_direction.inverse(), r.direction().inverse().normalize(), rHit.normal());
            return Color(k.x() * E.x(), k.y() * E.y(), k.z() * E.z());
        }
    }

private:
    bool inShadow(Vec3 hitP, Vec3 lightDir, Scene &scene) {
        Vec3 shadowRayDir = lightDir.inverse().normalize();
        Ray shadowRay = Ray(hitP.add(shadowRayDir.scale(0.01)), shadowRayDir);
        for (auto primitive : scene.primitives()) {
            RayHitResult res = primitive->intersection(shadowRay, 0.01, std::numeric_limits<float>::max());
            if (res.t() < std::numeric_limits<float>::max()) {
                return true;
            }
        }
    }

private:
    Color m_normalIntensity;
    Vec3 m_direction;
};

#endif //DEMO_RAY_TRACER_LIGHT_H
