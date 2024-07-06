#if !defined(MODEL_H)
#define MODEL_H

#include "my_lib/Core/Debug/Log.h"
#include "my_lib/Core/Maths/Vec3.h"
#include <cstdio>
#include <string.h>
#include <vector>
#include "my_lib/Bonus/Loading.h"

class Model
{
public:
    std::vector<unsigned int>   vertexIndices, uvIndices, normalIndices;
    std::vector<Vec3>           vertices, normals;
    std::vector<Vec2>           uvs;
    std::string                 filepath;
    Model();
    Model(const std::string& _filepath);
};

#endif
