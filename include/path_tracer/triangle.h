#ifndef path_tracer_triangle_h
#define path_tracer_triangle_h

#include "path_tracer/hitable.h"

class Triangle : public Hitable {
public:
    Triangle(Vec3 v0, Vec3 v1, Vec3 v2)
        : verts[0](v0), verts[1](v1), verts[2](v2) {}
    Triangle(Vec3 verts[3]) : verts(verts) {}
    
    
    Vec3 verts[3];
}

#endif
