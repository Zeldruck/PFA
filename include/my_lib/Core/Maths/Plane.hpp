#if !defined(PLANE_HPP)
#define PLANE_HPP
#include "Vec3.h"

class Plane
{
public:
    Vec3 normal;
    float distance; 
    inline Plane(const Vec3& point, const Vec3& _normal);
    inline float GetSignedDistanceToPlane(const Vec3& point);
    inline Vec3 GetClosestPointOnPlane(const Vec3& point);
    inline ~Plane();
};

inline Plane::Plane(const Vec3& point, const Vec3& _normal)
{
    normal      = _normal;
    distance    = DotProduct(point, _normal);
}

inline Plane::~Plane()
{}

inline float Plane::GetSignedDistanceToPlane(const Vec3& point)
{
    return distance - DotProduct(normal, point);
}

inline Vec3 Plane::GetClosestPointOnPlane(const Vec3& point)
{
    return point + (normal * GetSignedDistanceToPlane(point));
}

#endif // PLANE_HPP
