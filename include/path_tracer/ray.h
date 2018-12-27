#ifndef path_tracer_ray_h
#define path_tracer_ray_h

#include "path_tracer/vec3.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    
    Ray() {}
    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}

    Vec3 point_at_parameter(double t) const {
        return origin + t * direction;
    }
};

#endif
