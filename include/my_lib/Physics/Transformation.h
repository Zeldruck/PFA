
#if !defined(TRANSFORMATION_H)
#define TRANSFORMATION_H

#include "my_lib/Core/Maths/Mat4.h"

class Transformation
{
public:
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    Vec3 forward;
    Vec3 up;
    Vec3 right;
    Mat4 localRef;
    Mat4 worldRef;
    Transformation();
    ~Transformation();
};

#endif // TRANSFORMATION_H
