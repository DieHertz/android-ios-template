#ifndef __template__Math__
#define __template__Math__

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <algorithm>

namespace Math {
    template <typename T>
    T clamp(const T& value, const T& lb, const T& ub) {
        return std::max(lb, std::min(ub, value));
    }
    
    float radians(const float degrees);
    float degrees(const float radians);
    
    Vector3 cross(const Vector3&, const Vector3&);
    
    Matrix4 rotate(const Matrix4& m, float degrees, const Vector3& v);
}

#endif /* __template__Math__ */
