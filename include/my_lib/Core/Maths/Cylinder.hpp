#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_
#include "Vec3.h"
#include "Segment.hpp"

class FiniteCylinder
{
public :
    inline FiniteCylinder();
    inline FiniteCylinder(const Vec3&, const Vec3&, const float&, const float&);
    inline ~FiniteCylinder();
    Vec3    position, orientation;
    float   radius, length;
};

inline FiniteCylinder::FiniteCylinder()
{}

inline FiniteCylinder::FiniteCylinder ( const Vec3& _position, const Vec3& _orientation,
                            const float& _radius, const float& _length )
                            : radius {_radius}, length {_length}
{
    position = _position;
    orientation = _orientation;
    orientation.Normalize();
}

inline FiniteCylinder::~FiniteCylinder()
{}

class InfiniteCylinder
{
public:
    inline InfiniteCylinder(const Vec3&, const Vec3&, const float&);
    inline ~InfiniteCylinder();
    Vec3    position, orientation;
    float   radius;
};

inline InfiniteCylinder::InfiniteCylinder( const Vec3& _position, const Vec3& _orientation,
                            const float& _radius) : radius {_radius}
{
    position = _position;
    orientation = _orientation;
    orientation.Normalize();
}

inline InfiniteCylinder::~InfiniteCylinder()
{}

#endif
