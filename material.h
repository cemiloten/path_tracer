#ifndef path_tracer_material_h
#define path_tracer_material_h

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
    
    Vec3 albedo;
};

class Metal : public Material {
public:
    Metal(const Vec3& a, float f) : albedo(a) { fuzz = f < 1.0f ? f : 1.0f; }
    
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        Vec3 reflected = reflect(unit_vector(r_in.direction), record.normal);
        scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return dot(scattered.direction, record.normal) > 0.0f;
    }
    
    Vec3 albedo;
    float fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(float index_of_refraction) : ior(index_of_refraction) {}

    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        Vec3 outward_normal;
        float ni_over_nt;
        attenuation = Vec3(1.0f, 1.0f, 0.0f);
        Vec3 refracted;
    
        if (dot(r_in.direction, record.normal) > 0.0f) {
            outward_normal = -record.normal;
            ni_over_nt = ior;
        }
        else {
            outward_normal = record.normal;
            ni_over_nt = 1.0f / ior;
        }
    
        // Choose between reflection and refraction.
        if (refract(r_in.direction, outward_normal, ni_over_nt, refracted)) {
            scattered = Ray(record.p, refracted);
        }
        else {
            scattered = Ray(record.p, reflect(r_in.direction, record.normal));
            return false;
        }
        return true;
    }
    
    
    float ior;
};

#endif
