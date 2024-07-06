#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_
#include "Vec3.h"
#include "Segment.hpp"
#include "my_lib/Physics/HitBox.hpp"

class Sphere : public HitBox
{
public :
    inline Sphere();
    inline Sphere( Vec3, float );
    inline ~Sphere();

    inline bool CollisionBetweenTwoSphere( Sphere, Sphere );

    Vec3 position;
    float radius;
};

inline Sphere::Sphere()
{}

inline Sphere::Sphere( Vec3 _position, float _radius )
{
    position = _position;
    radius = _radius;
}

inline Sphere::~Sphere()
{}

inline bool Sphere::CollisionBetweenTwoSphere( Sphere S1, Sphere S2 )
{
    Vec3 VectorBetweenSpheres = S1.position - S2.position;
    float CollisionRadius = S1.radius + S2.radius;

    return VectorBetweenSpheres.GetMagnitude() < CollisionRadius;
}

bool IsSegmentIntersectingSphere(Segment seg, Sphere sphere);

#endif
