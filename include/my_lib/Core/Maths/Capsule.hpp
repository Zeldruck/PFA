#if !defined(CAPSULE_HPP)
#define CAPSULE_HPP

#include "Sphere.hpp"
#include "Cylinder.hpp"

class Capsule
{
public:
    float radius, length;
    Vec3 position, orientation;
    Sphere topSphere, bottomSphere;
    FiniteCylinder cyl;
    inline Capsule(const Vec3& _position, const float& _radius, const float& _length);
    inline ~Capsule();
};

inline Capsule::Capsule(const Vec3& _position, const float& _radius, const float& _length)
{
    position        = _position;
    radius          = _radius;
    length          = _length;

    orientation     = Vec3(0,1,0);

    topSphere       = Sphere(position + (orientation * (length / 2 )), radius);
    bottomSphere    = Sphere(position - (orientation * (length / 2 )), radius);
    
    cyl             = FiniteCylinder(position, orientation, radius, length);
}

inline Capsule::~Capsule()
{}


#endif // CAPSULE_HPP
