#ifndef material_h
#define material_h

#include "hitable.h"
#include "helpers.h"

class Material {
public:
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Vec3 albedo;

    Lambertian(const Vec3& a) : albedo(a) {}
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        Vec3 target = record.p + record.normal + random_in_unit_sphere();
        scattered = Ray(record.p, target - record.p);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material {
public:
    Vec3 albedo;

    Metal(const Vec3& a) : albedo(a) {}
    virtual bool scatter(
    const Ray& r_in,
    const HitRecord& record,
    Vec3& attenuation,
    Ray& scattered) const
    {
        Vec3 reflected = reflect(unit_vector(r_in.origin()), record.normal);
        scattered = Ray(record.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), record.normal) > 0.0f;
    }
};

#endif