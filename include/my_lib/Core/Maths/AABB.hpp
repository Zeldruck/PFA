#if !defined(AABB_HPP)
#define AABB_HPP

#include "Vec3.h"
#define NB_OF_AABB_FACE 6

class AABB
{
public:
    inline AABB(Vec3 _position, Vec3 _dimensions);
    inline ~AABB();
    Vec3 position;
    float width, height, depth;
};

inline AABB::AABB(Vec3 _position, Vec3 _dimensions)
{
    width   = _dimensions.x * 2;
    height  = _dimensions.y * 2;
    depth   = _dimensions.z * 2;

    position = _position;
}

inline AABB::~AABB()
{}

#endif // AABB_HPP
