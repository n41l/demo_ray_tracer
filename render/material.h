//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_MATERIAL_H
#define DEMO_RAY_TRACER_MATERIAL_H

#include <math.h>
#include "../core/color.h"
#include "../core/math.h"

class Material {
public:
    virtual Color evaluate(const Vec3 &lightDir, const Vec3 &viewerDir, const Vec3 &normal) = 0;
};

class BlinnPhongMaterial : public Material { ;

public:
    BlinnPhongMaterial(
            const Color &reflectance,
            const Color & specular,
            float phongExponent
    ): m_reflectance(reflectance), m_specularCoefficient(specular), m_phongExponent(phongExponent) {};

    Color evaluate(const Vec3 &lightDir, const Vec3 &viewerDir, const Vec3 &normal) override {
        Color L = m_reflectance.scale(1 / M_PI);
        Vec3 halfVector = lightDir.add(viewerDir).normalize();

        return L.add(m_specularCoefficient.scale(std::max(0.0f, powf(normal.dot(halfVector), m_phongExponent))));
    }


private:
    Color m_reflectance;
    Color m_specularCoefficient;
    float m_phongExponent;
};

#endif //DEMO_RAY_TRACER_MATERIAL_H
