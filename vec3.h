#ifndef path_tracer_vec3_h
#define path_tracer_vec3_h

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3 {
public:
    Vec3() { e[0] = e[1] = e[2] = 0.0f; }
    Vec3(float f) { e[0] = e[1] = e[2] = f; }
    Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const Vec3& operator + () const { return *this; }
    inline Vec3 operator - () const { return Vec3(-e[0], -e[1], -e[2]); }
    inline float operator [] (int index) const { return e[index]; }
    inline float& operator [] (int index) { return e[index]; };

    inline Vec3& operator += (const Vec3 &v2);
    inline Vec3& operator -= (const Vec3 &v2);
    inline Vec3& operator *= (const Vec3 &v2);
    inline Vec3& operator /= (const Vec3 &v2);
    inline Vec3& operator *= (const float t);
    inline Vec3& operator /= (const float t);

    inline float length() const {
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    inline float squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline void make_unit_vector() {
        float k = 1.0f / length();
        *this *= k;
    }

     inline Vec3 normalized() {
         float k = 1.0f / length();
         return Vec3(e[0] * k, e[1] * k, e[2] * k);
     }
    
    static const Vec3 zero;
    static const Vec3 one;

    float e[3];
};

const Vec3 Vec3::zero = Vec3(0.0f);
const Vec3 Vec3::one = Vec3(1.0f);

inline std::istream& operator >> (std::istream &is, Vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator << (std::ostream &os, const Vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline Vec3 operator + (const Vec3 &v1, const Vec3 &v2) {
    return Vec3(
        v1.e[0] + v2.e[0],
        v1.e[1] + v2.e[1],
        v1.e[2] + v2.e[2]);
}

inline Vec3 operator - (const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
        v1.e[0] - v2.e[0],
        v1.e[1] - v2.e[1],
        v1.e[2] - v2.e[2]);
}

inline Vec3 operator * (const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
        v1.e[0] * v2.e[0],
        v1.e[1] * v2.e[1],
        v1.e[2] * v2.e[2]);
}

inline Vec3 operator / (const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
        v1.e[0] / v2.e[0],
        v1.e[1] / v2.e[1],
        v1.e[2] / v2.e[2]);
}

inline Vec3 operator * (float t, const Vec3 &v) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator * (const Vec3 &v, float t) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator / (const Vec3 &v, float t) {
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(
         (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
        -(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0]),
         (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}

inline Vec3& Vec3::operator += (const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator -= (const Vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator *= (const Vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator /= (const Vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vec3& Vec3:: operator *= (const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vec3& Vec3:: operator /= (const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

#endif
