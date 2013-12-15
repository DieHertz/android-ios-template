//
//  Vector3.cpp
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//


#include "Vector3.h"
#include <math.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>

Vector3 Vector3::operator=(const Vector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& v) {
    return Vector3(x+v.x, y+v.y, z+v.z);
}

Vector3 Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& v) {
    return Vector3(x-v.x, y-v.y, z-v.z);
}

Vector3 Vector3::operator-() {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3 Vector3::operator*(const float a) {
    return Vector3(x*a, y*a, z*a);
}

Vector3 Vector3::operator*=(const float a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

float Vector3::operator*(const Vector3& v) {
    return (x*v.x + y*v.y + z*v.z);
}

Vector3 Vector3::operator/(const float a) {
    return Vector3(x/a, y/a, z/a);
}

Vector3 Vector3::operator/=(const float a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

float Vector3::lengthSQ() const {
    return x*x + y*y + z*z;
}

Vector3 Vector3::n() const {
    float inv = 1.0/std::sqrtf(x*x + y*y + z*z);
    return Vector3(x*inv, y*inv, z*inv);
}

float Vector3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

void Vector3::print() const {
    printf("Vector3(%.2f, %.2f, %.2f)\n", x, y, z);
}
