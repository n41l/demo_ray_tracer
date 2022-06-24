#include <iostream>
#include "math.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "scene.h"


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

    Sphere *s1 = new Sphere(Vec3(0.0f, 0.0f, -15.0f), 5, Vec3(1, 0, 0));
    Sphere *s2 = new Sphere(Vec3(5.0f, 3.0f, -20.0f), 8, Vec3(0, 1, 0));

    Scene scene = Scene();
    scene.addPrimitive(s1);
    scene.addPrimitive(s2);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            float u = viewportWidth * (i + 0.5) / imageWidth - halfVpWidth;
            float v = viewportHeight * (j + 0.5) / imageHeight - halfVpHeight;
            Ray r(eyePosition, horizontal.scale(u).add(vertical.scale(v)).add(Vec3(0.0, 0.0, -focalLength)));
            Color pixelColor = ray_color(r);

            RayHitResult rHit = scene.intersection(r, 0.0f, 100.0f);

            if (rHit.t() != std::numeric_limits<float>::max()) {
                pixelColor = rHit.primitive()->color();
            }

            write_color(std::cout, pixelColor);
        }
    }


    std::cerr << "\nDone.\n";

    return 0;
}
