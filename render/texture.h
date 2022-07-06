//
// Created by Kun Huang on 2022/7/6.
//

#ifndef DEMO_RAY_TRACER_TEXTURE_H
#define DEMO_RAY_TRACER_TEXTURE_H
#include "../core/core.h"

class Texture {
public:
    virtual Color value(float u, float v,  const Point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor() {}
    SolidColor(Color c) : m_color(c) {}
    SolidColor(float r, float g, float b) : SolidColor(Color(r, g, b)) {}

    virtual Color value(float u, float v, const Point3 &p) const override {
        return m_color;
    }

private:
    Color m_color;
};

#endif //DEMO_RAY_TRACER_TEXTURE_H
