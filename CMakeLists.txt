cmake_minimum_required(VERSION 3.21)
project(demo_ray_tracer)

set(CMAKE_CXX_STANDARD 14)


add_executable(demo_ray_tracer main.cpp math.h color.h primitive.h ray.h sphere.h scene.h)

#set(glm_DIR ./vendor/glm/cmake/glm)
#find_package(glm REQUIRED)
#target_link_libraries(demo_ray_tracer glm::glm)

