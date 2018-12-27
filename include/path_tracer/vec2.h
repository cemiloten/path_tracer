#ifndef path_tracer_vec2_h
#define path_tracer_vec2_h

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec2 {
public:
    static const Vec2 zero;
    static const Vec2 one;

    union {
        struct { double x, y; };
        struct { double u, v; };
        double e[2];
    };

    inline Vec2() { x = y = 0.0; }

    inline Vec2(double d) { x = y = d; }

    inline Vec2(float f) { x = y = double(f); }

    inline Vec2(int i) { x = y = double(i); }

    inline Vec2(double d0, double d1) : x(d0), y(d1) {}

    inline Vec2(float f0, float f1) : x(double(f0)), y(double(f1)) {}

    inline Vec2(int i0, int i1) : x(double(i0)), y(double(i1)) {}

    inline Vec2(const Vec2& v) : x(v.x), y(v.y) {}

    inline Vec2& operator = (const Vec2& v) {
        x = v.x; y = v.y;
        return *this;
    }

    inline const Vec2& operator + () const { return *this; }
    inline Vec2 operator - () const { return Vec2(-x, -y); }
    inline double operator [] (int index) const { return e[index]; }
    inline double& operator [] (int index) { return e[index]; };

    inline Vec2& operator += (const Vec2& v2);
    inline Vec2& operator -= (const Vec2& v2);
    inline Vec2& operator *= (const Vec2& v2);
    inline Vec2& operator /= (const Vec2& v2);
    inline Vec2& operator *= (const double t);
    inline Vec2& operator /= (const double t);

    inline double length() const {
        return sqrt(x*x + y*y);
    }

    inline double squared_length() const {
        return x*x + y*y;
    }

    inline void make_unit_vector() {
        double k = 1.0f / length();
        *this *= k;
    }

    inline Vec2 normalized() {
        double k = 1.0f / length();
        return Vec2(x * k, y * k);
    }
};

const Vec2 Vec2::zero = Vec2(0.0);
const Vec2 Vec2::one = Vec2(1.0);

inline std::istream& operator >> (std::istream& is, Vec2& v) {
    is >> v.x >> v.y;
    return is;
}

inline std::ostream& operator << (std::ostream& os, const Vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

inline Vec2 operator + (const Vec2& v1, const Vec2& v2) {
    return Vec2(
        v1.x + v2.x,
        v1.y + v2.y);
}

inline Vec2 operator - (const Vec2& v1, const Vec2& v2) {
    return Vec2(
        v1.x - v2.x,
        v1.y - v2.y);
}

inline Vec2 operator * (const Vec2& v1, const Vec2& v2) {
    return Vec2(
        v1.x * v2.x,
        v1.y * v2.y);
}

inline Vec2 operator / (const Vec2& v1, const Vec2& v2) {
    return Vec2(
        v1.x / v2.x,
        v1.y / v2.y);
}

inline Vec2 operator * (double t, const Vec2& v) {
    return Vec2(t * v.x, t * v.y);
}

inline Vec2 operator * (const Vec2& v, double t) {
    return Vec2(t * v.x, t * v.y);
}

inline Vec2 operator / (const Vec2& v, double t) {
    return Vec2(v.x / t, v.y / t);
}

inline double dot(const Vec2& v1, const Vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

inline Vec2& Vec2::operator += (const Vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

inline Vec2& Vec2::operator -= (const Vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

inline Vec2& Vec2::operator *= (const Vec2& v) {
    x *= v.x;
    y *= v.y;
    return *this;
}

inline Vec2& Vec2::operator /= (const Vec2& v) {
    x /= v.x;
    y /= v.y;
    return *this;
}

inline Vec2& Vec2:: operator *= (const double t) {
    x *= t;
    y *= t;
    return *this;
}

inline Vec2& Vec2:: operator /= (const double t) {
    x /= t;
    y /= t;
    return *this;
}

inline Vec2 unit_vector(Vec2 v) {
    return v / v.length();
}

#endif
