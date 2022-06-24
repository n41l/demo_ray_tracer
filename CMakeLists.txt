cmake_minimum_required(VERSION 3.21)
project(demo_ray_tracer)

set(CMAKE_CXX_STANDARD 14)


add_executable(demo_ray_tracer main.cpp core/math.h core/color.h render/primitive.h render/ray.h render/sphere.h render/scene.h render/light.h render/material.h)

#set(glm_DIR ./vendor/glm/cmake/glm)
#find_package(glm REQUIRED)
#target_link_libraries(demo_ray_tracer glm::glm)

