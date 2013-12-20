#include "MathFunctions.h"
#include <cmath>
#include <random>

namespace Math {
    Vector3 cross(const Vector3& a, const Vector3& b) {
        return {
            a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y
        };
    }
    
    float rnd(const float from, const float to) {
        std::random_device device;
        std::uniform_real_distribution<float> distr(from, to);
        return distr(device);
    };
    
    float radians(const float degrees) {
        return degrees * M_PI / 180;
    }
    
    float degrees(const float radians) {
        return radians * 180 / M_PI;
    }
    
    Matrix4 rotate(const Matrix4& m, const float degrees, const Vector3& u) {
        const float a = radians(degrees);
        const float sina = std::sin(a);
        const float cosa = std::cos(a);

        const float x = u.x;
        const float y = u.y;
        const float z = u.z;
        
        std::array<float, 16> r = {
            (1-cosa)*x*x + cosa,    (1-cosa)*x*y - sina*z,  (1-cosa)*x*z + sina*y,  0,
            (1-cosa)*y*x + sina*z,  (1-cosa)*y*y + cosa,    (1-cosa)*y*z - sina*x,  0,
            (1-cosa)*z*x - sina*y,  (1-cosa)*z*y + sina*x,  (1-cosa)*z*z + cosa,    0,
            0,                      0,                      0,                      1
        };

        return m * r;
    }
}
