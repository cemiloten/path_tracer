#include <fstream>
#include <limits>
#include <vector>
#include <chrono>
#include <thread>

#include "path_tracer/sphere.h"
#include "path_tracer/hitable_list.h"
#include "path_tracer/camera.h"
#include "path_tracer/material.h"
#include "path_tracer/xy_rect.h"
#include "path_tracer/image.h"
#include "path_tracer/thread_pool.h"
#include "path_tracer/sampler.h"


Vec3 color(const Ray& r, const Hitable* world, int depth)
{
    HitRecord record;
    /// test commment
    if (world->hit(r, 0.001, std::numeric_limits<double>::max(), record)) {
        Ray scattered;
        Vec3 attenuation;
        Vec3 emitted = record.material->emitted(record.u, record.v, record.p);
        if (depth < 50
            && record.material->scatter(r, record, attenuation, scattered))
        {
            return emitted + attenuation * color(scattered, world, depth + 1);
        }
        else {
            return emitted;
        }
    }
    
    return Vec3::zero;

    // Return sky color if no hit.
    Vec3 unit_direction = unit_vector(r.direction);
    double t = 0.5 * (unit_direction.y + 1.0); // -1:1 to 0:1
    return (1.0 - t) * Vec3::one + t * Vec3(0.5, 0.7, 1.0);
}


// TODO:
// sampling
// image
// multithreading
// triangles
// OpenGL
int main()
{
    int width = 600;
    int height = 400;

    Hitable* list[6];
    list[0] = new Sphere(
        Vec3(0, -1000, 0), 1000,
        new Lambertian(new CheckerTexture(
            new ConstantTexture(Vec3(0.2)),
            new ConstantTexture(Vec3(0.8)))));
    
    list[1] = new Sphere(
        Vec3(0, 3, 3), 1,
        new DiffuseLight(new ConstantTexture(0.7)));
    
    list[2] = new Sphere(
        Vec3(0, 2, 0), 2,
        new Lambertian(new ConstantTexture(Vec3(1.0, 0.5, 0.1))));
    
    list[3] = new XYRect(
        3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(1.0)));
    
    list[4] = new Sphere(
        Vec3(5.0, 1.1, 0.0), 1,
        new Lambertian(new ConstantTexture(Vec3(0.2, 0.4, 0.8))));
    
    list[5] = new Sphere(
        Vec3(3, 7, 2), 2,
        new DiffuseLight(new ConstantTexture(1.0)));
    
    // Objects
    Hitable* world = new HitableList(list, sizeof(list) / sizeof(Hitable*));
    
    Vec3 look_from(10, 2, 4);
    Vec3 look_at(0.0, 1.0, -0.5);
    
    double dist_to_focus = (look_from - look_at).length();
    Camera cam(
        look_from, look_at, Vec3(0, 1, 0),
        45.0, double(width) / double(height),
        0.0, dist_to_focus);
    
    Image image(width, height);
    auto start = std::chrono::high_resolution_clock::now();
    
    int spp = 64;
    bool jittered = true;
    std::string output_name;

    ThreadPool::ParallelFor(0, height, [&](int y) {
        for (int x = 0; x < width; x++) {
            Vec3 col;
            Sampler2D sampler(8, 8);
            output_name = "jittered_output2.ppm";
            for (int s = 0; s < sampler.n_sample; ++s) {
                Ray r = cam.get_ray(
                    (x + sampler.samples[s].x) / double(width),
                    (y + sampler.samples[s].y) / double(height));
                col += color(r, world, 0);
            }
            col /= double(sampler.n_sample);

            // Approximate gamma correction (~2.0)
            col = Vec3(sqrt(col.r), sqrt(col.g), sqrt(col.b));
            image.set_pixel(x, y, col);
        }
    });

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Render time: " << elapsed.count() << " seconds\n";

    image.save(output_name);

    return 0;
}
