#include "my_lib/Ressources/ResourcesManager.h"

std::ifstream ResourcesManager::Load(const std::string& filePath)
{
    std::ifstream file(filePath,std::ifstream::in);
    
    if (file)
    {
        return file;
    }
    
    else
    {
        Log::PrintError(Medium, "Load", "Error : impossible to open the file");
    }

    return file;
    
}

int ResourcesManager::CheckModel(const std::string& filepath)
{
    for (unsigned int i = 0; i < models.size() ; i++)
    {
        if ( models[i].filepath == filepath)
        {
            return i;
        }
    }
    
    return -1;
}

int ResourcesManager::CheckTexture(const std::string& filepath)
{
    for (unsigned int i = 0; i < textures.size() ; i++)
    {
        if ( textures[i].filepath == filepath)
        {
            return i;
        }
    }
    
    return -1;
}