#include "MathFunctions.h"

Vector3 cross(const Vector3 &a, const Vector3 &b) {
    return {a.y * b.z - b.y * a.z,
        a.z * b.x - b.z * a.x,
        a.x * b.y - b.x * a.y};
}
