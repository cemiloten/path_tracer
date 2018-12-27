#ifndef path_tracer_camera_h
#define path_tracer_camera_h

#include "path_tracer/ray.h"

class Camera {
public:
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u;
    Vec3 v;
    Vec3 w;
    double lens_radius;
    
    Camera(
        Vec3 look_from, Vec3 look_at, Vec3 view_up,
        double v_fov_in_degrees, double aspect_ratio,
        double aperture, double focus_distance)
            : origin(look_from), lens_radius(aperture / 2.0)
    {
        double theta = v_fov_in_degrees * M_PI / 180.0;
        double half_height = tan(theta / 2.0);
        double half_width = half_height * aspect_ratio;
    
        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(view_up, w));
        v = cross(w, u);
    
        lower_left_corner = origin
            - half_width * focus_distance * u
            - half_height * focus_distance * v
            - focus_distance * w;
        horizontal = 2.0 * half_width * focus_distance * u;
        vertical = 2.0 * half_height * focus_distance * v;
    }
    
    Ray get_ray(double s, double t) const {
        Vec3 rnd = lens_radius * random_in_unit_disk();
        Vec3 offset = u * rnd.x + v * rnd.y;
        Vec3 img_plane_pos = s * horizontal + t * vertical;
        return Ray(
            origin + offset,
            lower_left_corner + img_plane_pos - origin - offset);
    }
};

#endif
