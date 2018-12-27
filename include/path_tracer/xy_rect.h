#ifndef path_tracer_xy_rect_h
#define path_tracer_xy_rect_h

#include "path_tracer/hitable.h"
#include "path_tracer/material.h"

class XYRect : public Hitable {
public:
    double x0;
    double x1;
    double y0;
    double y1;
    double k;
    Material* material;
    
    XYRect() {}
    XYRect(double _x0, double _x1, double _y0, double _y1, double _k, Material* mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), material(mat) {}
    
    virtual bool hit(
        const Ray& r, double t_min, double t_max, HitRecord& record) const;
};

bool XYRect::hit(
    const Ray& r, double t_min, double t_max, HitRecord& record) const
{
    double t = (k - r.origin.z) / r.direction.z;
    if (t < t_min || t > t_max) {
        return false;
    }
    double x = r.origin.x + t * r.direction.x;
    double y = r.origin.y + t * r.direction.y;
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
