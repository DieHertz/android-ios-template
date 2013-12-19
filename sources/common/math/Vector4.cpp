#include "Vector4.h"

Vector4 Vector4::operator*(const Matrix4 &m) const {
    return {
        m.a[0]*x + m.a[4]*y + m.a[8]*z + m.a[12]*w,
        m.a[1]*x + m.a[5]*y + m.a[9]*z + m.a[13]*w,
        m.a[2]*x + m.a[6]*y + m.a[10]*z + m.a[14]*w,
        m.a[3]*x + m.a[7]*y + m.a[11]*z + m.a[15]*w
    };
}
