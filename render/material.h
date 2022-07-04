//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_MATERIAL_H
#define DEMO_RAY_TRACER_MATERIAL_H

#include <math.h>
#include "../core/core.h"
#include "ray.h"

class Material {
public:
    virtual bool scatter(const Ray& inRay, const RayHitResult& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : m_albedo(albedo) {}

    virtual bool scatter(const Ray &inRay, const RayHitResult &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 scatterDirection = rec.normal + Vec3::randomUnitVector();

        if (scatterDirection.nearZero())
            scatterDirection = rec.normal;

        scattered = Ray(rec.point, scatterDirection);
        attenuation = m_albedo;
        return true;
    }

private:
    Color m_albedo;
};

class Metal : public Material {
public:
    Metal(const Color& albedo) : m_albedo(albedo) {}

    virtual bool scatter(const Ray &inRay, const RayHitResult &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 reflected = reflect(inRay.direction().normalize(), rec.normal);
        scattered = Ray(rec.point, reflected);
        attenuation = m_albedo;
        return (scattered.direction().dot(rec.normal) > 0);
    }

private:
    Color m_albedo;
};

#endif //DEMO_RAY_TRACER_MATERIAL_H
