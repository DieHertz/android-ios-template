//
//  Vector3.cpp
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//


#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

Vector3::Vector3(const Vector4& v) {
    x = v.x;
    y = v.y;
    z = v.z;
};

Vector3& Vector3::operator=(const Vector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3 Vector3::operator*(const float a) const {
    return Vector3(x * a, y * a, z * a);
}

Vector3& Vector3::operator*=(const float a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

float Vector3::operator*(const Vector3& v) const {
    return (x * v.x + y * v.y + z * v.z);
}

Vector3 Vector3::operator/(const float a) const {
    return Vector3(x / a, y / a, z / a);
}

Vector3& Vector3::operator/=(const float a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

float Vector3::lengthSQ() const {
    return x * x + y * y + z * z;
}

Vector3 Vector3::n() const {
    const auto inv = 1 / std::sqrt(x*x + y*y + z*z);
    return Vector3(x * inv, y * inv, z * inv);
}

float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}
