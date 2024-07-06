#if !defined(MESH_H)
#define MESH_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "my_lib/Ressources/shader.h"
#include "my_lib/Ressources/Model.h"
#include "my_lib/Ressources/Texture.h"
#include "my_lib/Ressources/ResourcesManager.h"

Vec4 ColorConverter(Vec4 color);
Vec4 ColorEffect(Vec4 color);

class Mesh
{
public:
    Texture             texture;
    Model               model;
    Shader              shader;
    Vec4                color;
    unsigned int        VBO, VAO, texBuffer;
    Mesh();
    Mesh(const std::string& vertexShader, const std::string& fragementShader, const std::string& name, const std::string& object3D, ResourcesManager& resources, const std::string& textureFile = "", const float& mipmapScale = 1);
    void Draw(const Mat4& MVPMatrix);
    ~Mesh();
};

#endif // MESH_H
