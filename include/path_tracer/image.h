#ifndef path_tracer_image_h
#define path_tracer_image_h

#include <vector>
#include <string>
#include <iostream>

#include "path_tracer/vec3.h"

class Image {
public:
    Image(int w, int h) : width(w), height(h) {
        data = std::vector<Vec3>(width * height, Vec3(0.95, 0.6, 0.2));
    }

    friend inline std::ostream& operator<< (std::ostream& os, const Image& img);

    bool set_pixel(int x, int y, Vec3 color) {
        if (color.r < 0.0
            || color.g < 0.0
            || color.b < 0.0
            || color.r > 1.0
            || color.g > 1.0
            || color.b > 1.0)
        {
            return false;
        }

        data[x + y * width] = color;
        return true;
    }

    void save(const std::string& file_path) {
        std::ofstream out_file(file_path);
        out_file << "P3\n" << width << " " << height << "\n255\n";
        
        for (int y = height - 1; y >= 0; --y) {
            for (int x = 0; x < width; ++x) {
                Vec3 color = data[x + y * width];
                int ir = int(255.99 * color.r);
                int ig = int(255.99 * color.g);
                int ib = int(255.99 * color.b);
                out_file << ir << " " << ig << " " << ib << "\n";
            }
        }
        out_file.close();
    }

private:
    const int width;
    const int height;
    std::vector<Vec3> data;
};

inline std::ostream& operator<< (std::ostream& os, const Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            os << img.data[x + y * img.width] << " ";
        }
        os << "\n";
    }
    return os;
}

#endif
