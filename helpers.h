#include <random>

#include "vec3.h"

// Prepare for random number generation
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> rnd_zero_one(0.0f, 1.0f);

Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0f * Vec3(rnd_zero_one(gen), rnd_zero_one(gen), rnd_zero_one(gen)) - Vec3::one;
    } while (p.squared_length() >= 1.0f);
    return p;
}

Vec3 reflect(const Vec3& incoming, const Vec3& normal) {
    return incoming - 2.0f * dot(incoming, normal) * normal;
}