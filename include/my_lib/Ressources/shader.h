
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "my_lib/Core/Debug/Log.h"
#include "my_lib/Physics/Transformation.h"
#include "my_lib/Ressources/ResourcesManager.h"
#include "my_lib/Bonus/Loading.h"

class Shader
{
public:
    GLuint          ID;
    Shader          ();
    Shader          (const std::string& vertexPath, const std::string& fragmentPath, ResourcesManager* ressources);
    void Use        ();
    void SetBool    (const std::string& name, const bool&  value) const;
    void SetInt     (const std::string& name, const int&   value) const;
    void SetFloat   (const std::string& name, const float& value) const;
    void SetVec4    (const std::string& name, const Vec4&  value) const;
};
#endif
