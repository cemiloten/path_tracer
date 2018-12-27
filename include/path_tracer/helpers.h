#ifndef path_tracer_helpers_h
#define path_tracer_helpers_h

#include <random>

#include "path_tracer/vec3.h"

// Prepare for random number generation
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0.0, 1.0);

Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        // -1 <= p < 1
        p = 2.0 * Vec3(dis(gen), dis(gen), dis(gen)) - Vec3::one;
    } while (p.squared_length() >= 1.0);
    return p;
}

Vec3 random_in_unit_disk() {
    Vec3 p;
    do {
        // -1 <= p < 1
        p = 2.0 * Vec3(dis(gen), dis(gen), 0.0) - Vec3(1.0, 1.0, 0.0);
    } while (dot(p, p) >= 1.0);
    return p;
}

Vec3 reflect(const Vec3& v, const Vec3& normal) {
    return v - 2.0 * dot(v, normal) * normal;
}

bool refract(
    const Vec3& v_in, const Vec3& n, double eta, Vec3& refracted)
{
    Vec3 v_in_unit = unit_vector(v_in);
    double b = dot(v_in_unit, n);
    double discriminant = 1.0 - eta * eta * (1.0 - b * b);
    if (discriminant > 0.0) {
        refracted = eta * (v_in_unit - n * b) - n * sqrt(discriminant);
        return true;
    }
    return false;
}

double schlick(double cosine, double ior) {
    double r0 = (1.0 - ior) / (1.0 + ior);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}

#endif
