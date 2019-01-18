#ifndef path_tracer_sampler_h
#define path_tracer_sampler_h

#include <random>
#include <utility>

#include "path_tracer/vec2.h"


double randf01() {
    return distribution(generate);
}

class Sampler2D {
public:
    int n_samples;
    std::vector<Vec2> samples;

    Sampler2D(int detail_level) {
        n_samples = detail_level * detail_level;
        samples = std::vector<Vec2>(n_samples);
    }

    void generate() {
        int n = int(sqrt(n_samples));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                samples[j * n + i].x = (i + (j + randf01()) / n) / n;
                samples[j * n + i].y = (j + (i + randf01()) / n) / n;
            }
        }

        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                int k = j + randf01() * (n - j);
                std::swap(
                    samples[j * n + i].x,
                    samples[k * n + i].x);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int k = i + randf01() * (n - i);
                std::swap(
                    samples[j * n + i].y,
                    samples[k * n + i].y);
            }
        }
    }
    
private:
    std::random_device rnd;
    std::mt19937 generate(rnd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
};

#endif
