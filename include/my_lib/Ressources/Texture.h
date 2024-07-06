#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <glad/glad.h>
#include "my_lib/Ressources/stb_image.h"
#include "my_lib/Core/Debug/Log.h"
#include "my_lib/Bonus/Loading.h"

class Texture
{
public:
    GLuint index;
    std::string filepath;
    Texture();
    Texture(const std::string& filepath , int* width, int* height, int* nrChannels);
    ~Texture();
};

//Je ne peut pas mettre de const X& a cause de stbi_image qui veut des X*;
#endif // TEXTURE_H
