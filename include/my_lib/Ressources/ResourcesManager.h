#if !defined(RESOURCESMANAGER)
#define RESOURCESMANAGER

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "my_lib/Core/Debug/Log.h"
#include "my_lib/Ressources/Model.h"
#include "my_lib/Ressources/Texture.h"

class ResourcesManager
{
public:
    std::vector<Model>             models;
    std::vector<Texture>           textures;
    std::vector<unsigned int>      shaders;
    std::ifstream Load  (const std::string& filepath);
    int CheckModel      (const std::string& filepath);
    int CheckTexture    (const std::string& filepath);
};

#endif // RESOURCESMANAGER
