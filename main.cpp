#include <iostream>
#include <fstream>

#include "vec3.h"

int main()
{
    vec3 v = vec3(4.0f, 1.0f, 8.9f);
    vec3 v2 = vec3();

    vec3* vp = new vec3();
    std::unique_ptr<vec3> vpu = std::make_unique<vec3>(1.0f, 5.0f, 9.0f);

    int b = 10;
    int* a = &b;
    *a = 5;

    std::cout << v.x() << std::endl;
    std::cout << vp->x() << std::endl;
    std::cout << vpu->x() << std::endl;
    std::cout << v[0] << std::endl;
    float f = vpu->operator[](0);

    delete vp;
    vp = nullptr;

    // std::ofstream out_file("output.ppm");
    // int nx = 200;
    // int ny = 100;
    // out_file << "P3\n" << nx << " " << ny << "\n255\n";
    // for (int y = ny - 1; y >= 0; y--) {
    //     for (int x = 0; x < nx; x++) {
    //         float r = float(x) / float(nx);
    //         float g = float(y) / float(ny);
    //         float b = 0.2f;
    //         int ir = int(255.99 * r);
    //         int ig = int(255.99 * g);
    //         int ib = int(255.99 * b);
    //         out_file << ir << " " << ig << " " << ib << "\n";
    //     }
    // }
    // out_file.close();
}
