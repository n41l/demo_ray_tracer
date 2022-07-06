//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_MATERIAL_H
#define DEMO_RAY_TRACER_MATERIAL_H

#include "../core/core.h"
#include "ray.h"
#include "texture.h"

class Material {
public:
    virtual bool scatter(const Ray& inRay, const RayHitResult& rec, Color& attenuation, Ray& scattered) const = 0;
    virtual Color emitted(float u, float v, const Point3& point) const {
        return Color(0, 0, 0);
    }
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : m_albedo(make_shared<SolidColor>(albedo)) {}
    Lambertian(shared_ptr<Texture> tex) : m_albedo(tex) {}

    virtual bool scatter(const Ray &inRay, const RayHitResult &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 scatterDirection = rec.normal + Vec3::randomUnitVector();

        if (scatterDirection.nearZero())
            scatterDirection = rec.normal;

        scattered = Ray(rec.point, scatterDirection);
        attenuation = m_albedo->value(rec.u, rec.v, rec.point);
        return true;
    }

private:
    shared_ptr<Texture> m_albedo;
};

class Metal : public Material {
public:
    Metal(const Color& albedo, float f) : m_albedo(albedo), m_fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const Ray &inRay, const RayHitResult &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 reflected = reflect(inRay.direction().normalize(), rec.normal);
        scattered = Ray(rec.point, reflected + m_fuzz * Vec3::randomInUnitSphere());
        attenuation = m_albedo;
        return (scattered.direction().dot(rec.normal) > 0);
    }

private:
    Color m_albedo;
    float m_fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(float indexOfRefraction) : m_ir(indexOfRefraction) {}

    virtual bool scatter(const Ray &inRay, const RayHitResult &rec, Color &attenuation, Ray &scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        float etaiOverEtat = rec.isFrontFace ? (1.0 / m_ir) : m_ir;
        Vec3 unitInDir = inRay.direction().normalize();

        float cosTheta = fmin(unitInDir.inverse().dot(rec.normal), 1.0);
        float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = etaiOverEtat * sinTheta > 1.0;

        Vec3 outDir;
        if (cannotRefract || reflectance(cosTheta, etaiOverEtat) > Random::Float()) {
            outDir = reflect(unitInDir, rec.normal);
        } else {
            outDir = refract(unitInDir, rec.normal, etaiOverEtat);
        }
        scattered = Ray(rec.point, outDir);
        return true;
    }

private:
    static float reflectance(float cosine, float ri) {
        float r0 = (1 - ri) / (1 + ri);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow(1 - cosine, 5);
    }

private:
    float m_ir;
};

class diffuse_light : public Material {
public:
    diffuse_light(shared_ptr<Texture> tex) : m_emit(tex) {}
    diffuse_light(Color c) : m_emit(make_shared<SolidColor>(c)) {}

    bool scatter(const Ray &inRay, const RayHitResult &rec, Color &attenuation, Ray &scattered) const override {
        return false;
    }

    Color emitted(float u, float v, const Point3 &point) const override {
        return m_emit->value(u, v, point);
    }

private:
    shared_ptr<Texture> m_emit;
};


#endif //DEMO_RAY_TRACER_MATERIAL_H
