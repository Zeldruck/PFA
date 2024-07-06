
#if !defined(VEC2_H)
#define VEC2_H
#include <cmath>

class Vec2
{
public:
    float x;
    float y;
    Vec2();
    Vec2(float, float);
    Vec2(const Vec2&);
    ~Vec2();
    float GetMagnitude() const;
    void Normalize();
    Vec2 operator+(const Vec2&) const;
    Vec2 operator-(const Vec2&) const;    
    Vec2 operator*(float) const;
};

float DotProduct(const Vec2&, const Vec2&);
float AngleBetweenVectors(const Vec2&, const Vec2&);
float DistanceBetweenVectors(const Vec2&, const Vec2&);


#endif // VEC2_H
