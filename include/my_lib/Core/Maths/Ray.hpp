#if !defined(RAY_HPP)
#define RAY_HPP

#include "Vec3.h"

class Ray
{
public:
    Vec3 origin, direction; 
    inline Ray(const Vec3&, const Vec3&);
    inline ~Ray();
};

inline Ray::Ray(const Vec3& _origin, const Vec3& _direction)
{
    origin = _origin;
    direction = _direction;
}

inline Ray::~Ray()
{}


#endif // RAY_HPP
