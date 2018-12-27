#ifndef path_tracer_hitable_list_h
#define path_tracer_hitable_list_h

#include "path_tracer/hitable.h"

class HitableList: public Hitable {
public:
    Hitable** list;
    int list_size;
    
    HitableList() {}
    HitableList(Hitable** l, int n) : list(l), list_size(n) {}
    virtual bool hit(
        const Ray& r, double t_min, double t_max, HitRecord& record) const;
};

bool HitableList::hit(
    const Ray& r, double t_min, double t_max, HitRecord& record) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; ++i) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            record = temp_rec;
        }
    }
    return hit_anything;
}

#endif
