#if !defined(ORIENTEDBOX_HPP)
#define ORIENTEDBOX_HPP

#include <vector>
#include "Vec3.h"
#include "Sphere.hpp"
#include "Mat4.h"
#include <cmath>
#include "my_lib/Physics/HitBox.hpp"

#define NB_OF_OBB_AXIS 3
#define NB_OF_2_OBB_CROSS_AXIS 9

class OrientedBox : public HitBox
{
public:
    inline OrientedBox();
    inline OrientedBox(const Vec3& _position, const Vec3& _I, const Vec3& _J, const Vec3& _K);
    inline ~OrientedBox();
    Vec3 position;
    Vec3 I,J,K;
    float width, height, depth;
};

inline OrientedBox::OrientedBox()
{}

inline OrientedBox::OrientedBox(const Vec3& _position, const Vec3& _I, const Vec3& _J, const Vec3& _K)
{
    width       = _I.GetMagnitude() * 2;
    height      = _J.GetMagnitude() * 2;
    depth       = _K.GetMagnitude() * 2;
    
    position    = _position;

    I           = _I;
    J           = _J;
    K           = _K;

    I.Normalize();
    J.Normalize();
    K.Normalize();
}

inline OrientedBox::~OrientedBox()
{}

#endif // ORIENTEDBOX_HPP
