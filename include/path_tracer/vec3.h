#ifndef path_tracer_vec3_h
#define path_tracer_vec3_h

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3 {
public:
    static const Vec3 zero;
    static const Vec3 one;

    union {
        struct { double x, y, z; };
        struct { double r, g, b; };
        double e[3];
    };
    
    inline Vec3() { x = y = z = 0.0; }

    inline Vec3(double d) { x = y = z = d; }

    inline Vec3(float f) { x = y = z = double(f); }
    
    inline Vec3(int i) { x = y = z = double(i); }

    inline Vec3(double d0, double d1, double d2)
        : x(d0), y(d1), z(d2) {}
    
    inline Vec3(float f0, float f1, float f2)
        : x(double(f0)), y(double(f1)), z(double(f2)) {}

    inline Vec3(int i0, int i1, int i2)
        : x(double(i0)), y(double(i1)), z(double(i2)) {}

    inline Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}

    inline Vec3& operator = (const Vec3& v) {
        x = v.x; y = v.y; z = v.z;
        return *this;
    }

    inline const Vec3& operator + () const { return *this; }
    inline Vec3 operator - () const { return Vec3(-x, -y, -z); }
    inline double operator [] (int index) const { return e[index]; }
    inline double& operator [] (int index) { return e[index]; };

    inline Vec3& operator += (const Vec3& v2);
    inline Vec3& operator -= (const Vec3& v2);
    inline Vec3& operator *= (const Vec3& v2);
    inline Vec3& operator /= (const Vec3& v2);
    inline Vec3& operator *= (const double t);
    inline Vec3& operator /= (const double t);

    inline double length() const {
        return sqrt(x*x + y*y + z*z);
    }

    inline double squared_length() const {
        return x*x + y*y + z*z;
    }

    inline void make_unit_vector() {
        double k = 1.0f / length();
        *this *= k;
    }

     inline Vec3 normalized() {
         double k = 1.0f / length();
         return Vec3(x * k, y * k, z * k);
     }
};

const Vec3 Vec3::zero = Vec3(0.0);
const Vec3 Vec3::one = Vec3(1.0);

inline std::istream& operator >> (std::istream& is, Vec3& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

inline std::ostream& operator << (std::ostream& os, const Vec3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

inline Vec3 operator + (const Vec3& v1, const Vec3& v2) {
    return Vec3(
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z);
}

inline Vec3 operator - (const Vec3& v1, const Vec3& v2) {
    return Vec3(
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z);
}

inline Vec3 operator * (const Vec3& v1, const Vec3& v2) {
    return Vec3(
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z);
}

inline Vec3 operator / (const Vec3& v1, const Vec3& v2) {
    return Vec3(
        v1.x / v2.x,
        v1.y / v2.y,
        v1.z / v2.z);
}

inline Vec3 operator * (double t, const Vec3& v) {
    return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator * (const Vec3& v, double t) {
    return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator / (const Vec3& v, double t) {
    return Vec3(v.x / t, v.y / t, v.z / t);
}

inline double dot(const Vec3& v1, const Vec3& v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(
         (v1.y*v2.z - v1.z*v2.y),
        -(v1.x*v2.z - v1.z*v2.x),
         (v1.x*v2.y - v1.y*v2.x));
}

inline Vec3& Vec3::operator += (const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

inline Vec3& Vec3::operator -= (const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

inline Vec3& Vec3::operator *= (const Vec3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

inline Vec3& Vec3::operator /= (const Vec3& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

inline Vec3& Vec3:: operator *= (const double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

inline Vec3& Vec3:: operator /= (const double t) {
    x /= t;
    y /= t;
    z /= t;
    return *this;
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

#endif
