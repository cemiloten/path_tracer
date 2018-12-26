#include <fstream>
#include <limits>
#include <vector>
#include <chrono>
#include <thread>

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "xy_rect.h"
#include "image.h"

Vec3 color(const Ray& r, const Hitable* world, int depth)
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


// TODO:
// image
// multithreading
// triangles
// OpenGL

void render_row(int& y, int width, int height, int spp, const Camera& cam, const Hitable* world, Image& image) {
    for (int x = 0; x < width; x++) {
        Vec3 col = Vec3::zero;
        for (int s = 0; s < spp; ++s) {
            float u = float(x + dis(gen)) / float(width);
            float v = float(y + dis(gen)) / float(height);
            Ray r = cam.get_ray(u, v);
            col += color(r, world, 0);
        }
        col /= float(spp);

        // Approximate gamma correction (~2.0)
        col = Vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
        image.set_pixel(x, y, col);
    }
    
    y++;
}

int main()
{
    // Screen size
    int width = 400;
    int height = 200;
    int samplePerPixel = 32;

    Hitable* list[6];
    list[0] = new Sphere(
        Vec3(0, -1000, 0), 1000,
        new Lambertian(new CheckerTexture(
            new ConstantTexture(Vec3(0.2)),
            new ConstantTexture(Vec3(0.8)))));
    list[1] = new Sphere(
        Vec3(0, 3, 3), 1,
        new DiffuseLight(new ConstantTexture(0.7f)));
    
    list[2] = new Sphere(
        Vec3(0, 2, 0), 2,
        new Lambertian(new ConstantTexture(Vec3(1.0, 0.5, 0.1))));
    
    list[3] = new XYRect(
        3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(1.0f)));
    
    list[4] = new Sphere(
        Vec3(5, 1.1, 0), 1,
        new Lambertian(new ConstantTexture(Vec3(0.2, 0.4, 0.8))));
    
    list[5] = new Sphere(
        Vec3(3, 7, 2),
        2,
        new DiffuseLight(new ConstantTexture(1.0f)));
    
    // Objects
    Hitable* world = new HitableList(list, sizeof(list) / sizeof(Hitable*));
    
    Vec3 look_from(10, 2, 4);   
    Vec3 look_at(0, 1, -0.5);
    
    float dist_to_focus = (look_from - look_at).length();
    Camera cam(
        look_from, look_at, Vec3(0, 1, 0),
        45.0f, float(width) / float(height),
        0.15f, dist_to_focus);
    
    Image image(width, height);
    auto start = std::chrono::high_resolution_clock::now();

    int next_y = 0;
    std::vector<std::thread> threads(
        (int)std::thread::hardware_concurrency(),
        std::thread(render_row, &next_y, width, height, samplePerPixel, cam, world, image));

    //void render_row(int& y, int width, int height, int spp, const Camera& cam, const Hitable* world, Image& image)

    for (auto& t : threads) {
        t.join();
    }
    //std::cout << "Rendering... "
    //    << (int)((height - y) / (float)height * 100.0f) << "%\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    image.save("output.ppm");

    return 0;
}
