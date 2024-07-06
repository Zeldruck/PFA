
#if !defined(VEC4_H)
#define VEC4_H
#include "Vec3.h"

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;
    Vec4();
    Vec4(const Vec3&, float _w = 1.0f);
    Vec4(float, float, float, float);
    ~Vec4();
    float GetMagnitude() const;
    void Normalize();
    Vec4 operator+(const Vec4&);
    Vec4 operator*(float);
};

#endif // VEC4_H
