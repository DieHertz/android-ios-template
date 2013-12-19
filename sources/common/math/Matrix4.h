#ifndef __template__Matrix4__
#define __template__Matrix4__

#include <array>

struct Matrix4 {
    Matrix4() = default;
    Matrix4(std::array<float, 16>& arr) : a(arr) {}
    
    Matrix4 operator*(const Matrix4& rhs) const;
    
    std::array<float, 16> a = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
};



#endif /* __template__Matrix4__) */
