#ifndef __template__Vector3__
#define __template__Vector3__

class Vector4;

struct Vector3 {
    float x;
    float y;
    float z;
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vector3(const Vector4& v);
    
    Vector3& operator=(const Vector3& v);
    Vector3 operator+(const Vector3& v) const;
    Vector3& operator+=(const Vector3& v);
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator-() const;
    Vector3& operator-=(const Vector3& v);
    Vector3 operator*(const float a) const;
    Vector3& operator*=(const float a);
    float operator*(const Vector3& v) const;
    Vector3 operator/(const float a) const;
    Vector3& operator/=(const float a);
    float lengthSQ() const;
    float length() const;
    Vector3 n() const;
};


#endif /* __template__Vector3__ */
