//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_SCENE_H
#define DEMO_RAY_TRACER_SCENE_H

#include <vector>
#include "primitive.h"

class Scene: public Primitive {
public:
    Scene() : Primitive(nullptr) {};

    void addPrimitive(shared_ptr<Primitive> p) {
        m_ps.push_back(p);
    }

    std::vector<shared_ptr<Primitive>> primitives() const {
        return m_ps;
    }

    virtual bool boundingBox(Aabb &outputBox) const override {
        if (m_ps.empty()) return false;
        Aabb tempBox;
        bool isFirstBox = true;

        for (const auto& primitive: m_ps) {
            if (!primitive->boundingBox(tempBox)) return false;
            outputBox = isFirstBox ? tempBox : surroundingBox(outputBox, tempBox);
            isFirstBox = false;
        }

        return true;
    }

    virtual bool hit(const Ray &r, float t0, float t1, RayHitResult& res) override {
        bool hit = false;
        for (auto p : m_ps) {
            RayHitResult rHit;
            if (p->hit(r, t0, t1, rHit)) {
                res = rHit.t < res.t ? rHit : res;
                hit = true;
            }
        }
        return hit;
    }

private:
    std::vector<shared_ptr<Primitive>> m_ps = std::vector<shared_ptr<Primitive>>();
};

#endif //DEMO_RAY_TRACER_SCENE_H
