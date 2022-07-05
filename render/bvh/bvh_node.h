//
// Created by Kun Huang on 2022/7/5.
//

#ifndef DEMO_RAY_TRACER_BVH_NODE_H
#define DEMO_RAY_TRACER_BVH_NODE_H
#include "../../core/core.h"
#include "../primitive.h"
#include "../scene.h"
#include <algorithm>

class BVHNode : public Primitive {
public:
    BVHNode() : Primitive(nullptr) {};
    BVHNode(const Scene& scene) : BVHNode(scene.primitives(), 0, scene.primitives().size()) {};
    BVHNode(const std::vector<shared_ptr<Primitive>> &primitives, size_t start,
            size_t end);

    virtual bool hit(const Ray &r, float t0, float t1, RayHitResult& res) override;
    virtual bool boundingBox(Aabb &outputBox) const override;

private:
    shared_ptr<Primitive> m_left;
    shared_ptr<Primitive> m_right;
    Aabb m_box;
};

bool BVHNode::hit(const Ray &r, float t0, float t1, RayHitResult& res) {
    if (!m_box.hit(r, t0, t1))
        return false;
    bool hitLeft = m_left->hit(r, t0, t1, res);
    bool hitRight = m_right->hit(r, t0, hitLeft ? res.t : t1, res);

    return hitLeft || hitRight;
}

bool BVHNode::boundingBox(Aabb &outputBox) const {
    outputBox = m_box;
    return true;
}

inline bool boxCompare(const shared_ptr<Primitive> left, const shared_ptr<Primitive> right, int axis) {
    Aabb l_box;
    Aabb r_box;

    if (!left->boundingBox(l_box) || !right->boundingBox(r_box))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return l_box.min()[axis] < r_box.min()[axis];
}

bool boxXCompare(const shared_ptr<Primitive> left, const shared_ptr<Primitive> right) {
    return boxCompare(left, right, 0);
}

bool boxYCompare(const shared_ptr<Primitive> left, const shared_ptr<Primitive> right) {
    return boxCompare(left, right, 1);
}

bool boxZCompare(const shared_ptr<Primitive> left, const shared_ptr<Primitive> right) {
    return boxCompare(left, right, 2);
}

BVHNode::BVHNode(const std::vector<shared_ptr<Primitive>> &primitives, size_t start,
                 size_t end) : BVHNode() {
    auto objects = primitives;

    int axis = Random::Int(0, 2);
    auto comparator = (axis == 0) ? boxXCompare
                                                    : (axis == 1) ? boxYCompare
                                                    : boxZCompare;

    size_t size = end - start;

    if (size == 1) {
        m_left = m_right = objects[start];
    } else if (size == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            m_left = objects[start];
            m_right = objects[start + 1];
        } else {
            m_left = objects[start + 1];
            m_right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        auto mid = start + size / 2;
        m_left = make_shared<BVHNode>(objects, start, mid);
        m_right = make_shared<BVHNode>(objects, mid, end);
    }

    Aabb l_box, r_box;
    if (!m_left->boundingBox(l_box) || !m_right->boundingBox(r_box))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    m_box = surroundingBox(l_box, r_box);
}



#endif //DEMO_RAY_TRACER_BVH_NODE_H
