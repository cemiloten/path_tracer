#ifndef path_tracer_sphere_h
#define path_tracer_sphere_h

#include "path_tracer/hitable.h"
#include "path_tracer/material.h"

class Sphere: public Hitable {
public:
    Vec3 center;
    double radius;
    Material* material;
    
    Sphere() {}
    Sphere(Vec3 c, double r, Material* m) : center(c), radius(r), material(m) {}
    virtual bool hit(
        const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

bool Sphere::hit(
    const Ray& ray, double t_min, double t_max, HitRecord& record) const
{
    Vec3 oc = ray.origin - center;
    double a = dot(ray.direction, ray.direction);
    double b = dot(oc, ray.direction);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0.0f) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            record.material = material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            record.material = material;
            return true;
        }
    }
    return false;
}

#endif
