#include <fstream>
#include <limits>
#include <vector>
#include <random>

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

Vec3 color(const Ray& r, Hitable* world) {
    HitRecord record;
    if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), record)) {
        return 0.5f * (record.normal + Vec3::one);
    }
    // return sky color if no hit.
    Vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f); // -1:1 to 0:1
    return (1.0f - t) * Vec3::one + t * Vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    // Prepare for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    
    // Screen size
    int width = 200;
    int height = 100;
    int sampleCount = 100;

    // IO
    std::ofstream out_file("output.ppm");
    out_file << "P3\n" << width << " " << height << "\n255\n";

    Hitable* hitables[2];
    hitables[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
    hitables[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);
    Hitable* world = new HitableList(hitables, 2);

    Camera cam;
    
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            Vec3 col = Vec3::zero;
            for (int s = 0; s < sampleCount; ++s) {
                float u = float(x + dis(gen)) / float(width);
                float v = float(y + dis(gen)) / float(height);
                Ray r = cam.get_ray(u, v);
                //Vec3 p = r.point_at_parameter(2.0f);
                col += color(r, world);
            }
            col /= float(sampleCount);
            int ir = int(255.99 * col.x());
            int ig = int(255.99 * col.y());
            int ib = int(255.99 * col.z());

            out_file << ir << " " << ig << " " << ib << "\n";
        }
    }
    out_file.close();
    return 0;
}
