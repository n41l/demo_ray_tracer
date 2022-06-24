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
    void addPrimitive(Primitive *p) {
        m_ps.push_back(p);
    }

    virtual RayHitResult intersection(const Ray &r, float t0, float t1) override {
        RayHitResult res = RayHitResult::NotHit((Primitive *)this);
        for (auto p : m_ps) {
            RayHitResult rHit = p->intersection(r, t0, t1);
            if (rHit.t() < res.t()) {
                res = rHit;
            }
        }

        return res;
    }

private:
    std::vector<Primitive *> m_ps = std::vector<Primitive *>();
};

#endif //DEMO_RAY_TRACER_SCENE_H
