cmake_minimum_required(VERSION 3.0)

project(path_tracer)

# if (NOT WIN32)
#     add_definitions(-std=c++0x)
# endif()

include_directories(
    # My include files
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB PT_HEADERS
    "include/path_tracer/*.h")

file(GLOB PT_SOURCES
    "src/*.cpp")

add_executable(path_tracer
    ${PT_HEADERS}
    ${PT_SOURCES}
)
