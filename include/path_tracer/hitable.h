#ifndef path_tracer_hitable_h
#define path_tracer_hitable_h

#include "path_tracer/ray.h"

class Material;

struct HitRecord {
    double t;
    Vec3 p;
    Vec3 normal;
    Material* material;
    double u;
    double v;
};


class Hitable {
public:
    virtual bool hit(
        const Ray& r, double t_min, double t_max, HitRecord& record) const = 0;
};

#endif
