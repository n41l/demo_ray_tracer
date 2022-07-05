cmake_minimum_required(VERSION 3.21)
project(demo_ray_tracer)

set(CMAKE_CXX_STANDARD 17)

#include_directories(render core)

add_executable(demo_ray_tracer drt.h main.cpp)

#set(glm_DIR ./vendor/glm/cmake/glm)
#find_package(glm REQUIRED)
#target_link_libraries(demo_ray_tracer glm::glm)

