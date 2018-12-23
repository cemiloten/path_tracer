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
        // -1 <= p < 1
        p = 2.0f * Vec3(dis(gen), dis(gen), dis(gen)) - Vec3::one;
    } while (p.squared_length() >= 1.0f);
    return p;
}

Vec3 random_in_unit_disk() {
    Vec3 p;
    do {
        // -1 <= p < 1
        p = 2.0f * Vec3(dis(gen), dis(gen), 0.0f) - Vec3(1.0f, 1.0f, 0.0f);
    } while (dot(p, p) >= 1.0f);
    return p;
}

Vec3 reflect(const Vec3& v, const Vec3& normal) {
    return v - 2.0f * dot(v, normal) * normal;
}

bool refract(
    const Vec3& v_in, const Vec3& n, float eta, Vec3& refracted)
{
    Vec3 v_in_unit = unit_vector(v_in);
    float b = dot(v_in_unit, n);
    float discriminant = 1.0f - eta * eta * (1.0f - b * b);
    if (discriminant > 0.0f) {
        refracted = eta * (v_in_unit - n * b) - n * sqrt(discriminant);
        return true;
    }
    return false;
}

float schlick(float cosine, float ior) {
    float r0 = (1.0f - ior) / (1.0f + ior);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * powf((1.0f - cosine), 5.0f);
}

#endif
