#if !defined(SCENE_H)
#define SCENE_H

#include "my_lib/Core/DataStructure/GameObject.hpp"
#include "my_lib/Bonus/Loading.h"
#include "my_lib/Ressources/ResourcesManager.h"

void LoadObject         (const std::string& filePath, GameObject<OrientedBox>* world, ResourcesManager& resources);
void LoadObjectWithTag  (const std::string& filePath, GameObject<OrientedBox>* world, ResourcesManager& resources, const std::string& _tag);
void LoadMap            (const std::string& filePath, GameObject<OrientedBox>* world, ResourcesManager& resources, const std::string& _tag, float widthW, float heightW, GLFWwindow* window);

#endif // SCENE_H


//J'ai des doutes concernant le bon fonctionnement du parsing je devrais le revoir !