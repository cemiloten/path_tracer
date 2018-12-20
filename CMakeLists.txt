cmake_minimum_required(VERSION 3.0.0)
project(path_tracer VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(path_tracer main.cpp)
target_sources(path_tracer
    PUBLIC vec3.h ray.h hitable.h sphere.h hitable_list.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
