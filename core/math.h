//
// Created by Kun Huang on 2022/6/24.
//
#ifndef DEMO_RAY_TRACER_MATH_H
#define DEMO_RAY_TRACER_MATH_H

#include <math.h>
#include "random.h"
#include "utilities.h"

namespace math {
    template <typename T>
    T clamp(const T& n, const T& lower, const T& upper) {
        return std::max(lower, std::min(n, upper));
    }
}


class Vec3 {
public:
    Vec3(): m_ps{0, 0, 0} {};
    Vec3(float x, float y, float z): m_ps{x, y, z} {};

    float operator[](int i) const { return m_ps[i]; }
    float& operator[](int i) {return m_ps[i]; }

    Vec3& operator+=(const Vec3 &other) {
        m_ps[0] += other.m_ps[0];
        m_ps[1] += other.m_ps[1];
        m_ps[2] += other.m_ps[2];
        return *this;
    }

    Vec3& operator*=(const float s) {
        m_ps[0] *= s;
        m_ps[1] *= s;
        m_ps[2] *= s;
        return *this;
    }

    Vec3& operator/=(const float s) {
        return *this *= 1/s;
    }

    inline float dot(const Vec3 &other) const { return m_ps[0] * other.m_ps[0] + m_ps[1] * other.m_ps[1] + m_ps[2] * other.m_ps[2]; }
    inline Vec3 cross(const Vec3 &other) const {
        float x = m_ps[1] * other.m_ps[2] - m_ps[2] * other.m_ps[1],
              y = m_ps[2] * other.m_ps[0] - m_ps[0] * other.m_ps[2],
              z = m_ps[0] * other.m_ps[1] - m_ps[1] * other.m_ps[0];
        return Vec3(x, y, z);
    }
    inline float magnitudeSquare() const {
        return m_ps[0] * m_ps[0] + m_ps[1] * m_ps[1] + m_ps[2] * m_ps[2];
    }

    inline float length() const {
         return sqrt(magnitudeSquare());
    }

    inline Vec3 normalize() const {
        float length = sqrt(this->magnitudeSquare());
        return Vec3(m_ps[0] / length, m_ps[1] / length, m_ps[2] / length);
    }

    inline Vec3 inverse() const {
        return Vec3(-m_ps[0], -m_ps[1], -m_ps[2]);
    }

    inline Vec3 clamp(float lower, float upper) const {
        return Vec3(math::clamp(m_ps[0], lower, upper), math::clamp(m_ps[1], lower, upper), math::clamp(m_ps[2], lower, upper));
    }

    bool nearZero() const {
        const float s = 1e-8;
        return (fabs(m_ps[0]) < s) && (fabs(m_ps[1]) < s) && (fabs(m_ps[2]) < s);
    }

    float x() const { return m_ps[0]; }
    float y() const { return m_ps[1]; }
    float z() const { return m_ps[2]; }

    inline static Vec3 random() {
        return Vec3(Random::Float(), Random::Float(), Random::Float());
    }

    inline static Vec3 random(float min, float max) {
        return Vec3(Random::Float(min, max), Random::Float(min, max), Random::Float(min, max));
    }

    inline static Vec3 randomInUnitSphere() {
        while (true) {
            Vec3 p = Vec3::random(-1, 1);
            if (p.length() >= 1) continue;
            return p;
        }
    }

    static Vec3 randomUnitVector() {
        return randomInUnitSphere().normalize();
    }

private:
    float m_ps[3];
};

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.x(), t*v.y(), t*v.z());
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

inline Vec3 reflect(const Vec3& in, const Vec3& normal) {
    return in - 2 * in.dot(normal) * normal;
}

using Color = Vec3;
using Point3 = Vec3;

#endif //DEMO_RAY_TRACER_MATH_H
