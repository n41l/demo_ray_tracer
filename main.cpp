#include <iostream>
#include "core/math.h"
#include "core/color.h"
#include "render/ray.h"
#include "render/sphere.h"
#include "render/scene.h"
#include "render/light.h"
#include "render/plane.h"


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

    BlinnPhongMaterial *mat1 = new BlinnPhongMaterial(
            Color(0.1, 1.0, 1.0),
            Color(1.0, 1.0, 1.0),
            1
            );
    BlinnPhongMaterial *mat2 = new BlinnPhongMaterial(
            Color(1.0, 1.0, 1.0),
            Color(1.0, 1.0, 1.0),
            50
            );
    BlinnPhongMaterial *mat3 = new BlinnPhongMaterial(
            Color(1.0, 1.0, 1.0),
            Color(0.5, 0.5, 0.5),
            1
    );

    NormalColorMaterial *mat4 = new NormalColorMaterial();

    Sphere *s1 = new Sphere(Vec3(0.0f, 0.0f, -15.0f), 5, mat4);
    Sphere *s2 = new Sphere(Vec3(5.0f, 3.0f, -20.0f), 8, mat2);
    Plane * plane = new Plane(Vec3(0.0f,-5.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), mat3);

    Scene scene = Scene();
    scene.addPrimitive(s1);
    scene.addPrimitive(s2);
    scene.addPrimitive(plane);

    std::vector<Light*> lights;
    lights.push_back(new PointLight(Vec3(5.0f, 10.0f, -5.0f), Color(20.0f, 20.0f, 20.0f)));
    lights.push_back(new DirectionLight(Vec3(1.0f, -1.0f, -1.0f).normalize(), Color(1.0f, 1.0f, 1.0f)));

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            float u = viewportWidth * (i + 0.5) / imageWidth - halfVpWidth;
            float v = viewportHeight * (j + 0.5) / imageHeight - halfVpHeight;
            Ray r(eyePosition, horizontal.scale(u).add(vertical.scale(v)).add(Vec3(0.0, 0.0, -focalLength)));
            Color pixelColor = ray_color(r);

            RayHitResult rHit = scene.intersection(r, 0.0f, 1000.0f);

            if (rHit.t < std::numeric_limits<float>::max()) {
                pixelColor = Vec3(0.0f, 0.0f, 0.0f);
                for(auto light : lights) {
                    pixelColor = pixelColor.add(light->illuminate(r, rHit, scene));
                }

                pixelColor = pixelColor.clamp(0.0f, 1.0f);
            }

            write_color(std::cout, pixelColor);
        }
    }


    std::cerr << "\nDone.\n";

    return 0;
}
