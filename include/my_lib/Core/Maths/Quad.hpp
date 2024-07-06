#if !defined(QUAD_HPP)
#define QUAD_HPP

#include "Vec3.h"

class Quad
{
public:
    Vec3 position, I, J, K;
    float Ix, Iy;
    inline Quad(const Vec3& _position, const Vec3& _I, const Vec3& _J, const Vec3& _K);
    inline ~Quad();
};

inline Quad::Quad(const Vec3& _position, const Vec3& _I, const Vec3& _J, const Vec3& _K)
{
    position    = _position;
    Ix          = (_I.GetMagnitude());
    Iy          = (_J.GetMagnitude());
    I           = _I;
    J           = _J;
    K           = _K;

    I.Normalize();
    J.Normalize();
    K.Normalize();
}

inline Quad::~Quad()
{}


#endif // QUAD_HPP
