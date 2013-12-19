#include "Matrix4.h"
#include <stdio.h>

Matrix4 Matrix4::operator*(const Matrix4& rhs) const {
	std::array<float, 16> c;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            c[i + j*4] = 0;
            for (int k = 0; k < 4; k++)
                c[i + j*4] += a[i + k*4]*rhs.a[k + 4*j];
        }
    }
    
    return Matrix4(c);
}
