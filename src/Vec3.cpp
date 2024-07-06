#include "../include/my_lib/Core/Maths/Vec3.h"
#include <iostream>

Vec3::Vec3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3::Vec3(const Vec3& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

float Vec3::GetMagnitude() const
{
    return sqrt( ( x * x )  + ( y * y ) + ( z * z ) );
}

void Vec3::Normalize()
{
    float length = GetMagnitude();
	x /= length;
	y /= length;
	z /= length;
}

Vec3 Vec3::operator+(const Vec3& vec1) const
{
    Vec3 vec3;
    vec3.x = x + vec1.x;
    vec3.y = y + vec1.y;
    vec3.z = z + vec1.z;
    return vec3;
}

Vec3 Vec3::operator-(const Vec3& vec1) const
{
    Vec3 vec3;
    vec3.x = x - vec1.x;
    vec3.y = y - vec1.y;
    vec3.z = z - vec1.z;
    return vec3;
}

Vec3 Vec3::operator*(float a) const
{
    Vec3 vec3;
    vec3.x = x * a;
    vec3.y = y * a;
    vec3.z = z * a;
    return vec3;
}

Vec3 CrossProduct(const Vec3& u, const Vec3& v)
{
    return {u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x};
} 

float CrossProduct2D(const Vec3& u, const Vec3& v)
{
    return u.x * v.y - v.x * u.y;
}

float DotProduct(const Vec3& u, const Vec3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float AngleBetweenVectors(const Vec3& u, const Vec3& v)
{
    return acos(DotProduct(u, v) / (u.GetMagnitude() * v.GetMagnitude()));
}

float DistanceBetweenVectors(const Vec3& u, const Vec3& v)
{
    return sqrt(((v.x - u.x) * (v.x - u.x)) + ((v.y - u.y) * (v.y - u.y)) + ((v.z - u.z) * (v.z - u.z)));
}

float ScalarTriple(const Vec3& a, const Vec3& b ,const Vec3& c)
{
    return DotProduct(a, CrossProduct(b,c));
}

Vec3 operator*(const float& x, const Vec3& vec)
{
    return vec * x;
}

void Print(const Vec3& vec)
{
    std::cout << "X = " << vec.x << ";Y = " << vec.y << ";Z = " << vec.z << ";" << std::endl;
}

Vec3 operator*(const Vec3& Vec1, const Vec3& Vec2)
{
    return Vec3( Vec1.x*Vec2.x,
                 Vec1.y*Vec2.y,
                 Vec1.z*Vec2.z );
}

Vec3 DegreesToRadians(const Vec3& vec)
{
    Vec3 tempVec;
    if(vec.x != 0)
        tempVec.x   =   M_PI/(180/vec.x);
    else
        tempVec.x   =   0;

    if(vec.y != 0)
        tempVec.y   =   M_PI/(180/vec.y);
    else
        tempVec.y   =   0;

    if(vec.z != 0)
        tempVec.z   =   M_PI/(180/vec.z);
    else
        tempVec.z   =   0;

    return tempVec;
}

Vec3 worldToLocal(const Vec3& pos, const Vec3& origin, const Vec3& I, const Vec3& J, const Vec3& K)
{
    return Vec3( DotProduct(pos - origin,I),
		            DotProduct(pos - origin,J),
                    DotProduct(pos - origin,K));
}

Vec3::~Vec3()
{}