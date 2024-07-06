#include "my_lib/Ressources/Texture.h"

Texture::Texture()
{}

Texture::Texture(const std::string& fileName, int* width, int* height, int* nrChannels)
{
    Loading::Print(Large, " Texture creation started ! ");
    
    Loading::Print(Small, "Generate the texture ...  ");
    
    glGenTextures(1, &index);
    glBindTexture(GL_TEXTURE_2D, index);

    Loading::Print(Small, "Set the texture ...  ");
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Loading::Print(Small, "Flip the texture ...  ");

    stbi_set_flip_vertically_on_load(true);

    Loading::Print(Small, "Open the file ...  ");
    
    unsigned char* data = stbi_load(fileName.c_str(), width, height, nrChannels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else
        Log::PrintError(Low, "stdbi_load()", "Failed to load texture");

    Loading::Print(Small, "free the texture ...  ");

    stbi_image_free(data);

    Loading::Print(Large, " Texture creation complete ! ");
}

Texture::~Texture()
{}
