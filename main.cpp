#include <iostream>
#include "drt.h"

Color ray_color(const Ray& r, const Color& background, BVHNode node, int depth) {
    RayHitResult res;
    res.t = std::numeric_limits<float>::max();
    if (depth <= 0)
        return Color(0, 0, 0);

    if (!node.hit(r, 0.001, std::numeric_limits<float>::max(), res))
        return background;

    Ray scattered;
    Color attenuation;
    Color emitted = res.matPtr->emitted(res.u, res.v, res.point);


    if (!res.matPtr->scatter(r, res, attenuation, scattered)) {
        return emitted;
    }

    return emitted + attenuation * ray_color(scattered, background, node, depth - 1);
}

Scene cornellBox() {
    Scene box;
    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(Color(15, 15, 15));

    box.addPrimitive(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    box.addPrimitive(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    box.addPrimitive(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    box.addPrimitive(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    box.addPrimitive(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    box.addPrimitive(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<Primitive> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = make_shared<RotateY>(box1, 15);
    box1 = make_shared<Translate>(box1, Vec3(265,0,295));
    box.addPrimitive(box1);

    shared_ptr<Primitive> box2 = make_shared<Box>(Point3(0,0,0), Point3(165,165,165), white);
    box2 = make_shared<RotateY>(box2, -18);
    box2 = make_shared<Translate>(box2, Vec3(130,0,65));
    box.addPrimitive(box2);

    return box;
}

int main() {

    const float aspectRatio = 1.0;
    const int imageWidth = 600;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;
    const Color background(0, 0, 0);
    Point3 lookFrom = Point3(278, 278, -800);
    Point3 lookAt = Point3(278, 278, 0);
    float vFov = 40.0;

    Camera camera(lookFrom, lookAt, Vec3(0,1,0),  vFov, aspectRatio);

    Scene scene = cornellBox();

    BVHNode root = BVHNode(scene);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                float u = (i + Random::Float()) / float(imageWidth - 1);
                float v = (j + Random::Float()) / float(imageHeight - 1);
                Ray r = camera.getRay(u, v);
                pixelColor += ray_color(r, background, root, maxDepth);
            }
            write_color(std::cout, pixelColor, samplesPerPixel);
        }
    }


    std::cerr << "\nDone.\n";

    return 0;
}
