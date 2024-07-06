
#if !defined(VEC3_H)
#define VEC3_H
#include "Vec2.h"
#include <iostream>

# define M_PI           3.14159265358979323846

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float, float, float);
    Vec3(const Vec3&);
    ~Vec3();
    float GetMagnitude() const;
    void Normalize();
    Vec3 operator+(const Vec3&) const;
    Vec3 operator-(const Vec3&) const;    
    Vec3 operator*(float) const;
};

Vec3 operator*(const float& x, const Vec3& vec);
Vec3 operator*(const Vec3& Vec1, const Vec3& Vec2);

void Print(const Vec3& vec);

Vec3    CrossProduct            (const Vec3&, const Vec3&);
float   CrossProduct2D          (const Vec3&, const Vec3&);
float   DotProduct              (const Vec3&, const Vec3&);
float   AngleBetweenVectors     (const Vec3&, const Vec3&);
float   DistanceBetweenVectors  (const Vec3&, const Vec3&);
float   ScalarTriple            (const Vec3&, const Vec3&,const Vec3&);
Vec3    DegreesToRadians        (const Vec3&);
void    Print                   (const Vec3&);
Vec3    worldToLocal            (const Vec3& pos, const Vec3& origin, const Vec3& I, const Vec3& J, const Vec3& K);

#endif // VEC3_H
