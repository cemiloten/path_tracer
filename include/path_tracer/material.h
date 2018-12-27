#ifndef path_tracer_material_h
#define path_tracer_material_h

#include "path_tracer/hitable.h"
#include "path_tracer/helpers.h"
#include "path_tracer/texture.h"

class Material {
public:
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const = 0;
    
    virtual Vec3 emitted(double u, double v, Vec3& p) const {
        return Vec3::zero;
    }
};


class Lambertian : public Material {
public:
    Texture* albedo;
    
    Lambertian(Texture* tex) : albedo(tex) {}
    
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        Vec3 target = record.p + record.normal + random_in_unit_sphere();
        scattered = Ray(record.p, target - record.p);
        attenuation = albedo->value(0, 0, record.p);
        return true;
    }
};


class Metal : public Material {
public:
    Texture* albedo;
    double fuzz;
    
    Metal(Texture* tex, double f) : albedo(tex) {
        fuzz = f < 1.0f ? f : 1.0f;
    }
    
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        Vec3 reflected = reflect(unit_vector(r_in.direction), record.normal);
        scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo->value(0, 0, record.p);
        return dot(scattered.direction, record.normal) > 0.0f;
    }
};


class Dielectric : public Material {
public:
    double ior;

    Dielectric(double index_of_refraction) : ior(index_of_refraction) {}

    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        Vec3 outward_normal;
        double eta; // greek letter η -> η2/η1
        attenuation = Vec3(1.0f, 1.0f, 1.0f);
        Vec3 reflected = reflect(r_in.direction, record.normal);
        Vec3 refracted;
        double reflect_prob;
        double cosine;
        double in_dot_n = dot(r_in.direction, record.normal);
    
        if (dot(r_in.direction, record.normal) > 0.0f) {
            outward_normal = -record.normal;
            eta = ior;
            cosine = ior * in_dot_n / r_in.direction.length();
        }
        else {
            outward_normal = record.normal;
            eta = 1.0f / ior;
            cosine = -in_dot_n / r_in.direction.length();
        }
    
        if (refract(r_in.direction, outward_normal, eta, refracted)) {
            reflect_prob = schlick(cosine, ior);
        }
        else {
            reflect_prob = 1.0f;
        }
    
        if (dis(gen) < reflect_prob) {
            scattered = Ray(record.p, reflected);
        }
        else {
            scattered = Ray(record.p, refracted);
        }
    
        return true;
    }
};


class DiffuseLight : public Material {
public:
    Texture* emit;
    
    DiffuseLight(Texture* tex) : emit(tex) {}

    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& record,
        Vec3& attenuation,
        Ray& scattered) const
    {
        return false;
    }
    
    virtual Vec3 emitted(double u, double v, Vec3& p) const {
        return emit->value(u, v, p);
    }
};

#endif
