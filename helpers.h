#ifndef path_tracer_helpers_h
#define path_tracer_helpers_h

#include <random>

#include "vec3.h"

// Prepare for random number generation
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0.0f, 1.0f);

Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0f * Vec3(dis(gen), dis(gen), dis(gen)) - Vec3::one;
    } while (p.squared_length() >= 1.0f);
    return p;
}

Vec3 reflect(const Vec3& v, const Vec3& normal) {
    return v - 2.0f * dot(v, normal) * normal;
}

bool refract(
    const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
{
    Vec3 unit = unit_vector(v);
    float dt = dot(unit, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if (discriminant > 0.0f) {
        refracted = ni_over_nt * (unit - n * dt) - n * sqrt(discriminant);
        return true;
    }
    return false;
}

#endif
