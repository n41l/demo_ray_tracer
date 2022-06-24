//
// Created by Kun Huang on 2022/6/24.
//
#ifndef DEMO_RAY_TRACER_MATH_H
#define DEMO_RAY_TRACER_MATH_H

#include <math.h>

class Vec3 {
public:
    Vec3(float x, float y, float z): m_x(x), m_y(y), m_z(z) {};

    inline Vec3 add(const Vec3 &other) {
        return Vec3(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z);
    };
    inline Vec3 scale(float value) {
        return Vec3(this->m_x * value, this->m_y * value, this->m_z * value);
    };
    inline float dot(const Vec3 &other) { return this->m_x * other.m_x + this->m_y * other.m_y + this->m_z * other.m_z; }
    inline Vec3 cross(const Vec3 &other) {
        float x = this->m_y * other.m_z - this->m_z * other.m_y,
              y = this->m_z * other.m_x - this->m_x * other.m_z,
              z = this->m_x * other.m_y - this->m_y * other.m_x;
        return Vec3(x, y, z);
    }
    inline float magnitudeSquare() {
        return this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z;
    }
    inline Vec3 normalize() {
        float length = sqrt(this->magnitudeSquare());
        return Vec3(m_x / length, m_y / length, m_z / length);
    }

    float x() const { return m_x; }
    float y() const { return m_y; }
    float z() const { return m_z; }

private:
    float m_x, m_y, m_z;
};

using Color = Vec3;

#endif //DEMO_RAY_TRACER_MATH_H