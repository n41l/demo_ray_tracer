//
// Created by Kun Huang on 2022/6/24.
//

#ifndef DEMO_RAY_TRACER_SCENE_H
#define DEMO_RAY_TRACER_SCENE_H

#include <vector>
#include "primitive.h"

class Scene: public Primitive {
public:
    Scene() {};
    void addPrimitive(Primitive *p) {
        m_ps.push_back(p);
    }

    virtual RayHitResult intersection(const Ray &r, float t0, float t1) override {
        RayHitResult res = RayHitResult::NotHit((Primitive *)this, r);
        for (auto p : m_ps) {
            RayHitResult rHit = p->intersection(r, t0, t1);
            if (rHit.t() < res.t()) {
                res = rHit;
            }
        }

        return res;
    }

    virtual Color color() const override {
        return Vec3(0.0f, 0.0f, 0.0f);
    };

private:
    std::vector<Primitive *> m_ps = std::vector<Primitive *>();
};

#endif //DEMO_RAY_TRACER_SCENE_H
