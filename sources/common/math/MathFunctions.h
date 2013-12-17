//
//  Math.h
//  template
//
//  Created by Alexander Pavlov on 17.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#ifndef __template__Math__
#define __template__Math__

#include <algorithm>

namespace Math {
    template <typename T>
    T clamp(const T& value, const T& lb, const T& ub) {
        return std::max(lb, std::min(ub, value));
    }
}

#endif /* defined(__template__Math__) */
