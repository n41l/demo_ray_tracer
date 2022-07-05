//
// Created by Kun Huang on 2022/7/4.
//

#ifndef DEMO_RAY_TRACER_RANDOM_H
#define DEMO_RAY_TRACER_RANDOM_H
#include <cstdlib>


class Random {
public:
    static inline float Float() {
        return rand() / (RAND_MAX + 1.0);
    }


    static inline float Float(float min, float max) {
        return min + (max - min) * Float();
    }

    static inline int Int(int min, int max) {
        return static_cast<int>(Float(min, max + 1));
    }
};

#endif //DEMO_RAY_TRACER_RANDOM_H
