#include "my_lib/Core/DataStructure/GameObject.hpp"

template<typename T>
float GameObject<T>::time      = 0;
template<typename T>
float GameObject<T>::deltatime = 0;
template<typename T>
std::vector<GameObject<OrientedBox>* > GameObject<T>::map;
template<typename T>
std::vector<GameObject<OrientedBox>* > GameObject<T>::animObject;

template<typename T> 
GameObject<T>::GameObject()
{
    activeInHierarchy   = false;
    printable           = false;
    tag                 = "";
    name                = "";
}

template<> GameObject<Sphere>::GameObject()
{
    activeInHierarchy   = false;
    printable           = false;
    tag                 = "";
    name                = "";
}

//Sphere

template<> GameObject<Sphere>::GameObject(const Vec3& _position, const Vec3& _rotation, const Vec3& _scale, const std::string& _name, const std::string& _tag)
{
    activeInHierarchy   = false;
    printable           = false;
    tag                 = _tag;
    name                = _name;
    transform           = Graph(_position, _rotation, _scale);
}

//End

//OrientedBox

template<> GameObject<OrientedBox>::GameObject(const Vec3& _position, const Vec3& _rotation, const Vec3& _scale, const std::string& _name, const std::string& _tag)
{
    activeInHierarchy   = false;
    printable           = false;
    tag                 = _tag;
    name                = _name;
    transform           = Graph(_position, _rotation, _scale);

    hitbox              = OrientedBox(transform.position,
                                transform.right     * 5 * transform.scale.x,
                                transform.up        * 5 * transform.scale.y,
                                transform.forward   * 5 * transform.scale.z);
}

//End

template<typename T> 
GameObject<T>::~GameObject()
{}

template<typename T> 
void GameObject<T>::setTime(const float& actualTime, const float& _deltaTime)
{
    deltatime   = _deltaTime;
    time        = actualTime;
}

template<typename T> 
void GameObject<T>::LoadMap(const std::vector<GameObject<OrientedBox>*>& _map)
{
    map = _map;
}

template<typename T> 
void GameObject<T>::ChildrensProcess(const Mat4& viewMat , const Mat4& projectionMat)
{
  transform.localRef  = Mat4::CreateTransformMatrix(transform.position,transform.rotation,transform.scale);
  Mat4 worldRef2 = transform.localRef * transform.worldRef;
  Process(worldRef2, viewMat , projectionMat);
  for (GameObject* child : children)
  {
    child->transform.worldRef = worldRef2;
    child->ChildrensProcess(viewMat , projectionMat);
  }
}

template<typename T> 
void GameObject<T>::Process(const Mat4& modelMat, const Mat4& viewMat , const Mat4& projectionMat)
{
    if (activeInHierarchy)
    {
        Mat4 MVPMatrix;
        MVPMatrix = projectionMat * viewMat * modelMat;
        MVPMatrix.Transpose();

        /*if (tag == "Player")
        {
            GroundCheck();
        }*/

        if (printable)
        {
            mesh.Draw(MVPMatrix);
        }
    }
}

template class GameObject<OrientedBox>;
template class GameObject<Sphere>;