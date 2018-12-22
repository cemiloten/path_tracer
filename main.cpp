#include <fstream>
#include <limits>
#include <vector>

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

Vec3 color(const Ray& r, Hitable* world, int depth)
{
    HitRecord record;
    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), record)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50
            && record.material->scatter(r, record, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else {
            return Vec3::zero;
        }
    }

    // Return sky color if no hit.
    Vec3 unit_direction = unit_vector(r.direction);
    float t = 0.5f * (unit_direction.y() + 1.0f); // -1:1 to 0:1
    return (1.0f - t) * Vec3::one + t * Vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
    // Screen size
    int width = 200;
    int height = 100;
    int sampleCount = 50;

    // IO
    std::ofstream out_file("output.ppm");
    out_file << "P3\n" << width << " " << height << "\n255\n";

    // Objects
    Hitable* hitables[4];
    
    hitables[0] = new Sphere(
        Vec3( 0.0f, 0.0f, -1.0f), 0.5f,
        new Lambertian(Vec3(0.8f, 0.3f, 0.3f)));
    
    hitables[1] = new Sphere(
        Vec3( 1.0f, 0.0f, -1.0f), 0.5f,
        new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.3f));
    
    hitables[2] = new Sphere(
        Vec3(-1.0f, 0.0f, -1.0f), 0.5f,
        new Metal(Vec3(0.8f, 0.8f, 0.8f), 0.8f));
    
    hitables[3] = new Sphere(
        Vec3( 0.0f, -100.5f, -1.0f), 100.0f,
        new Lambertian(Vec3(0.8f, 0.8f, 0.0f)));
    
    Hitable* world = new HitableList(hitables, 4);
    Camera cam;
    
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            Vec3 col = Vec3::zero;
            for (int s = 0; s < sampleCount; ++s) {
                float u = float(x + dis(gen)) / float(width);
                float v = float(y + dis(gen)) / float(height);
                Ray r = cam.get_ray(u, v);
                //Vec3 p = r.point_at_parameter(2.0f);
                col += color(r, world, 0);
            }
            col /= float(sampleCount);

            // Approximate gamma correction (~2.0)
            col = Vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());

            out_file << ir << " " << ig << " " << ib << "\n";
        }
    }
    out_file.close();
    return 0;
}
