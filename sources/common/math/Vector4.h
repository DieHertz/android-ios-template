#ifndef __template__Vector4__
#define __template__Vector4__

#include "Vector3.h"
#include "Matrix4.h"
#include <array>

struct Vector4 {
    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z) {}
    Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
    
    Vector4 operator*(const Matrix4& m) const;
    
    float x;
    float y;
    float z;
    float w;
};

#endif /* __template__Vector4__ */
