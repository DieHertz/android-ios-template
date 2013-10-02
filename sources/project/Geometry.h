#ifndef Geometry_h
#define Geometry_h

#include <cmath>

struct Vertex3 {
    float x;
    float y;
    float z;
};

struct Triangle {
    Vertex3 a;
    Vertex3 b;
    Vertex3 c;
};

struct Line {
    Vertex3 a;
    Vertex3 b;
};

inline Vertex3 operator +(const Vertex3& lhs, const Vertex3& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline Vertex3 operator *(const Vertex3& v, const float f) {
    return { v.x * f, v.y * f, v.z * f };
}

inline Vertex3 operator /(const Vertex3& v, const float f) {
    return { v.x / f, v.y / f, v.z / f };
}

inline float length(const Vertex3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

#endif /* Geometry_h */
