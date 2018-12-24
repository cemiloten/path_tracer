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
    float t = 0.5f * (unit_direction.y() + 1.0f); // -1:1 to 0:1
    return (1.0f - t) * Vec3::one + t * Vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
    // Screen size
    int width = 400;
    int height = 400;
    int samplePerPixel = 128;

    // IO
    std::ofstream out_file("output.ppm");
    out_file << "P3\n" << width << " " << height << "\n255\n";

    Hitable* list[4];
    list[0] = new Sphere(
        Vec3(0, -1000, 0), 1000,
        new Lambertian(new CheckerTexture(
            new ConstantTexture(Vec3(0.2)),
            new ConstantTexture(Vec3(0.8)))));
    list[1] = new Sphere(
        Vec3(-1, 1, 1), 0.2,
        new Lambertian(new ConstantTexture(Vec3(0.2, 0.4, 0.8))));
    list[2] = new Sphere(
        Vec3(1, 1, 1), 0.5,
        new Lambertian(new ConstantTexture(Vec3(1.0, 0.5, 0.1))));
    list[3] = new Sphere(
        Vec3(0, 3, 2), 1,
        new DiffuseLight(new ConstantTexture(Vec3((1.0f)))));
    
    // Objects
    Hitable* world = new HitableList(list, sizeof(list) / sizeof(Hitable*));
    
    Vec3 look_from(2, 2, 5);
    Vec3 look_at(
        (reinterpret_cast<Sphere*>(list[1])->center
        + reinterpret_cast<Sphere*>(list[2])->center) / 2);
    
    float dist_to_focus = (look_from - look_at).length();
    Camera cam(
        look_from, look_at, Vec3(0, 1, 0),
        45.0f, float(width) / float(height),
        0.15f, dist_to_focus);
    
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            Vec3 col = Vec3::zero;
            for (int s = 0; s < samplePerPixel; ++s) {
                float u = float(x + dis(gen)) / float(width);
                float v = float(y + dis(gen)) / float(height);
                Ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(samplePerPixel);

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
