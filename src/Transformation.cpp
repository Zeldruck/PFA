#include "my_lib/Physics/Transformation.h"

Transformation::Transformation()
{
    position    = Vec3(0,0,0);
    rotation    = Vec3(0,0,0);
    scale       = Vec3(0,0,0);
    forward      = Vec3(0,0,0);
    up          = Vec3(0,0,0);
    right       = Vec3(0,0,0);
    localRef    = Mat4::Identity();
    worldRef    = Mat4::Identity();
}

Transformation::~Transformation()
{}