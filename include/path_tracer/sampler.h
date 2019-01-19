#ifndef path_tracer_sampler_h
#define path_tracer_sampler_h

#include <random>
#include <utility>

#include "path_tracer/vec2.h"


<<<<<<< HEAD
double randf01() {
    return distribution(generate);
=======
std::random_device rd2;
std::mt19937 generate(rd2());
std::uniform_real_distribution<double> distr(0.0, 1.0);

double rand01() {
    return distr(generate);
>>>>>>> 9877889199d3b8ed27a5479d048f5b5e44f179ca
}

// Correlated multi-jittered sampling from Pixar graphics paper.
// https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf
class Sampler2D {
public:
    int n_col;
    int n_row;
    int n_sample;
    
    // The matrix is stored one column after another in one dimension.
    Vec2* samples;

    Sampler2D(int m, int n) : n_row(m), n_col(n) {
        n_sample = n_col * n_row;
        samples = new Vec2[n_sample];
        generate();
    }

    ~Sampler2D() {
        delete[] samples;
        samples = nullptr;
    }

private:
    void generate() {
        int m = n_row;
        int n = n_col;

        // m * n matrix, elements accessed as {row i, col j}
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                samples[i + j * m].x = (i + (j + rand01()) / double(n)) / double(m);
                samples[i + j * m].y = (j + (i + rand01()) / double(m)) / double(n);
            }
        }

        // Swap x coords in each column.
        for (int j = 0; j < n; ++j) {
            int k = j + rand01() * (n - j);
            for (int i = 0; i < m; ++i) {
                double temp = samples[i + j * m].x;
                samples[i + j * m].x = samples[i + k * m].x;
                samples[i + k * m].x = temp;
            }
        }

        // Swap y coords in each row.
        for (int i = 0; i < m; ++i) {
            int k = i + rand01() * (m - i);
            for (int j = 0; j < n; ++j) {
                double temp = samples[i + j * m].y;
                samples[i + j * m].y = samples[k + j * m].x;
                samples[k + j * m].x = temp;
            }
        }
    }
    
private:
    std::random_device rnd;
    std::mt19937 generate(rnd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
};

#endif
