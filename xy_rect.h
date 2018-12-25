#ifndef path_tracer_xy_rect_h
#define path_tracer_xy_rect_h

#include "hitable.h"
#include "material.h"

class XYRect : public Hitable {
public:
    float x0;
    float x1;
    float y0;
    float y1;
    float k;
    Material* material;
    
    XYRect() {}
    XYRect(float _x0, float _x1, float _y0, float _y1, float _k, Material* mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), material(mat) {}
    
    virtual bool hit(
        const Ray& r, float t_min, float t_max, HitRecord& record) const;
};

bool XYRect::hit(
    const Ray& r, float t_min, float t_max, HitRecord& record) const
{
    float t = (k - r.origin.z()) / r.direction.z();
    if (t < t_min || t > t_max) {
        return false;
    }
    float x = r.origin.x() + t * r.direction.x();
    float y = r.origin.y() + t * r.direction.y();
    if (x < x0 || x > x1 || y < y0 || y > y1) {
        return false;
    }
    record.u = (x - x0) / (x1 - x0);
    record.v = (y - y0) / (y1 - y0);
    record.t = t;
    record.material = material;
    record.p = r.point_at_parameter(t);
    record.normal = Vec3(0, 0, 1);
    return true;
}

#endif
