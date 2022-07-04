#include <iostream>
#include "drt.h"

Color ray_color(const Ray& r, Scene s, int depth) {
    RayHitResult res = s.intersection(r, 0.001, std::numeric_limits<float>::max());

    if (depth <= 0)
        return Color(0, 0, 0);

    if (res.t < std::numeric_limits<float>::max()) {
        Ray scattered;
        Color attenuation;
        if (res.matPtr->scatter(r, res, attenuation, scattered)) {
            return attenuation * ray_color(scattered, s, depth - 1);
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = r.direction().normalize();
    auto t = 0.5*(unit_direction.y() + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0f - t) + Color(0.5, 0.7, 1.0) * t;
}

int main() {

    const float aspectRatio = 16.0 / 9.0;
    const int imageWidth = 512;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 10;
    const int maxDepth = 50;

    Camera camera;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2));

    Scene scene = Scene();
    scene.addPrimitive(make_shared<Plane>(Vec3(0.0f,-5.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), material_ground));
    scene.addPrimitive(make_shared<Sphere>(Vec3(0.0f, 0.0f, -15.0f), 5, material_center));
    scene.addPrimitive(make_shared<Sphere>(Vec3(-10.0f, 0.0f, -15.0f), 5, material_left));
    scene.addPrimitive(make_shared<Sphere>(Vec3(10.0f, 0.0f, -15.0f), 5, material_right));

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                float u = (i + Random::Float()) / float(imageWidth - 1);
                float v = (j + Random::Float()) / float(imageHeight - 1);
                Ray r = camera.getRay(u, v);
                pixelColor += ray_color(r, scene, maxDepth);
            }
            write_color(std::cout, pixelColor, samplesPerPixel);
        }
    }


    std::cerr << "\nDone.\n";

    return 0;
}
