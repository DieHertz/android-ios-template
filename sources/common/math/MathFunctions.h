#ifndef __template__Math__
#define __template__Math__

#include "Vector3.h"
#include <algorithm>

namespace Math {
    template <typename T>
    T clamp(const T& value, const T& lb, const T& ub) {
        return std::max(lb, std::min(ub, value));
    }
    
    Vector3 cross(const Vector3&, const Vector3&);
}

#endif /* __template__Math__ */
