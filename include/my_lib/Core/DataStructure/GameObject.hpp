#if !defined(GAMEOBJECT_HPP)
#define GAMEOBJECT_HPP

#include <iostream>
#include "my_lib/Physics/Transformation.h"
#include "my_lib/Core/DataStructure/Graph.h"
#include "my_lib/LowRenderer/Mesh.h"
#include "my_lib/Physics/HitBox.hpp"
#include "my_lib/Core/Maths/OrientedBox.hpp"

template<typename T>
class GameObject
{
public:
    static float                                    time; 
    static float                                    deltatime;
    static std::vector<GameObject<OrientedBox>*>    map;
    static std::vector<GameObject<OrientedBox>*>    animObject;
    bool                                            activeInHierarchy; 
    bool                                            printable;
    std::string                                     tag;
    std::string                                     name;
    std::vector<GameObject<T>*>                     children;
    Graph                                           transform;
    Mesh                                            mesh;
    T                                               hitbox;
    float                                           cooldown;   
    GameObject                          ();
    GameObject                          (const Vec3& _position, const Vec3& _rotation, const Vec3& scale, const std::string& name = "", const std::string& tag = "");
    ~GameObject                         ();
    virtual void ChildrensProcess       (const Mat4& viewMat , const Mat4& projectionMat);
    virtual void Process                (const Mat4& modelMat, const Mat4& viewMat , const Mat4& projectionMat);
    static  void LoadMap                (const std::vector<GameObject<OrientedBox>*>& _map);
    static  void setTime                (const float& actualTime, const float& _deltaTime);
};

#endif // GAMEOBJECT_HPP
