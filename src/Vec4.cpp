#include "../include/my_lib/Core/Maths/Vec4.h"

Vec4::Vec4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

float Vec4::GetMagnitude() const
{
    return sqrt( ( x * x )  + ( y * y ) + ( z * z ) + ( w * w ) );
}

void Vec4::Normalize()
{
    float length = GetMagnitude();
	x /= length;
	y /= length;
	z /= length;
    w /= length;
}

Vec4::Vec4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4::Vec4(const Vec3& vec3, float _w)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = _w;
}

Vec4 Vec4::operator+(const Vec4& vec1)
{
    Vec4 vec4;
    vec4.x = x + vec1.x;
    vec4.y = y + vec1.y;
    vec4.z = z + vec1.z;
    vec4.w = w + vec1.w;
    return vec4;
}

Vec4 Vec4::operator*(float a)
{
    Vec4 vec4;
    vec4.x = x * a;
    vec4.y = y * a;
    vec4.z = z * a;
    vec4.w = w * a;
    return vec4;
}

Vec4::~Vec4()
{}