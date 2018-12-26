cmake_minimum_required(VERSION 3.0)

project(path_tracer)

if (NOT WIN32)
    add_definitions(-std=c++0x)
endif()

file(GLOB SOURCE_FILES
    "*.h"
    "*.cpp"
)

add_executable(path_tracer ${SOURCE_FILES})
