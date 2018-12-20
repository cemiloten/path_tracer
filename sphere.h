#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class Sphere: public Hitable {
public:
    Sphere() {}
    Sphere(Vec3 c, float r) : center(c), radius(r) {};
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;

    Vec3 center;
    float radius;
};

bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const {
    Vec3 oc = ray.origin() - center;
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0.0f) {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif