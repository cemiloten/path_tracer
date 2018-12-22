#ifndef path_tracer_ray_h
#define path_tracer_ray_h

#include "vec3.h"

class Ray {
public:
    Ray() {}
    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}
    Vec3 point_at_parameter(float t) const { return origin + t * direction; }
    
    Vec3 origin;
    Vec3 direction;
};

#endif
