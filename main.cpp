#include <iostream>
#include "math.h"
#include "color.h"

class Ray {
public:
    Ray(const Vec3& o, const Vec3& d): m_origin(o), m_direction(d) {};
    Vec3 origin() const { return m_origin; }
    Vec3 direction() const { return m_direction; }

    Vec3 evaluate(float t) {
        return m_origin.add(m_direction.scale(t));
    }

private:
    Vec3 m_origin, m_direction;
};

Color ray_color(const Ray& r) {
    Vec3 unit_direction = r.direction().normalize();
    auto t = 0.5*(unit_direction.y() + 1.0);
    return Color(1.0, 1.0, 1.0).scale(1.0f - t).add(Color(0.5, 0.7, 1.0).scale(t));
}

int main() {
    int imageWidth = 512, imageHeight = 512;

    Vec3 eyePosition = Vec3(0.0f, 0.0f, 0.0f);
    float focalLength = 1.0f;
    float viewportWidth = 2.0f;
    float viewportHeight = 2.0f;
    float halfVpWidth = viewportWidth * 0.5;
    float halfVpHeight = viewportHeight * 0.5;
    Vec3 horizontal = Vec3(1.0f, 0.0f, 0.0f);
    Vec3 vertical = Vec3(0.0f, 1.0f, 0.0f);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            float u = viewportWidth * (i + 0.5) / imageWidth - halfVpWidth;
            float v = viewportHeight * (j + 0.5) / imageHeight - halfVpHeight;
            Ray r(eyePosition, horizontal.scale(u).add(vertical.scale(v)).add(Vec3(0.0, 0.0, -focalLength)));
            Color pixelColor = ray_color(r);
            write_color(std::cout, pixelColor);
        }
    }


    std::cerr << "\nDone.\n";

    return 0;
}
