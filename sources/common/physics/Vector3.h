//
//  Vector3.h
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#ifndef __template__Vector3__
#define __template__Vector3__

class Vector3 {
public:
    union {
        float data[3];
        struct {
            float x, y, z;
        };
    };
    
    Vector3() { x = 0; y = 0; z = 0; };
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; };
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {};
    
    Vector3 operator=(const Vector3& v);
    Vector3 operator+(const Vector3& v);
    Vector3 operator+=(const Vector3& v);
    Vector3 operator-(const Vector3& v);
    Vector3 operator-();
    Vector3 operator-=(const Vector3& v);
    Vector3 operator*(const float a);
    Vector3 operator*=(const float a);
    float operator*(const Vector3& v);
    Vector3 operator/(const float a);
    Vector3 operator/=(const float a);
    float lengthSQ() const;
    float length() const;
    Vector3 n() const;
    
    void print(void) const;
};


#endif /* defined(__template__Vector3__) */
