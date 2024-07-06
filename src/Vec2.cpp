#include "../include/my_lib/Core/Maths/Vec2.h"

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::Vec2(const Vec2& v)
{
    this->x = v.x;
    this->y = v.y;
}

float Vec2::GetMagnitude() const
{
    return sqrt( ( x * x )  + ( y * y ) );
}

void Vec2::Normalize()
{
    float length = GetMagnitude();
	x /= length;
	y /= length;
}

Vec2 Vec2::operator+(const Vec2& vec1) const
{
    Vec2 Vec2;
    Vec2.x = x + vec1.x;
    Vec2.y = y + vec1.y;
    return Vec2;
}

Vec2 Vec2::operator-(const Vec2& vec1) const
{
    Vec2 Vec2;
    Vec2.x = x - vec1.x;
    Vec2.y = y - vec1.y;
    return Vec2;
}

Vec2 Vec2::operator*(float a) const
{
    Vec2 Vec2;
    Vec2.x = x * a;
    Vec2.y = y * a;
    return Vec2;
}

float DotProduct(const Vec2& u, const Vec2& v)
{
    return u.x * v.x + u.y * v.y;
}

float AngleBetweenVectors(const Vec2& u, const Vec2& v)
{
    return acos(DotProduct(u, v) / (u.GetMagnitude() * v.GetMagnitude()));
}

float DistanceBetweenVectors(const Vec2& u, const Vec2& v)
{
    return sqrt(((v.x - u.x) * (v.x - u.x)) + ((v.y - u.y) * (v.y - u.y)));
}

Vec2::~Vec2()
{}