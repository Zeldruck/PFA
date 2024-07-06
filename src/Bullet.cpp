#include "../include/my_lib/Bullet.hpp"
#include "../include/my_lib/Core/DataStructure/GameObject.hpp"

std::vector<Enemy*>* Bullet::enemyList;

Bullet::Bullet(ResourcesManager& rs, const Vec3& _bulletScale, const Vec3& shootPos, const Vec3& _direction, const float& _hitboxRadius, const float& _speed, const float& _bulletLiveTime, const int& _damage) 
: Rigidbody(shootPos, _hitboxRadius, "Bullet", "Bullet")
{
    activeInHierarchy   = true;
    printable           = true;
    mesh                = Mesh("./ressources/Shaders/shader.vs", "./ressources/Shaders/shader.fs", "Bullet", "./ressources/Models/Primitives/sphere.obj", rs, "./ressources/Textures/bullet.png");
    transform.forward   = _direction;
    transform.forward.Normalize();
    speed               = _speed;
    damage              = _damage;
    transform.scale     = _bulletScale;
    transform.worldRef  = Mat4::CreateTransformMatrix(transform.position, Vec3(0.f, 0.f, 0.f), transform.scale);
    bulletLiveTime      = _bulletLiveTime;
}

Bullet::~Bullet()
{}

void Bullet::Destroy(const Vec3& hitpoint, ResourcesManager& rs)
{
    animObject.push_back(new GameObject<OrientedBox>(hitpoint, Vec3(0,0,0), Vec3(1,1,1), "Cube", "Cube"));
    animObject[animObject.size()-1]->activeInHierarchy  = true;
    animObject[animObject.size()-1]->cooldown           = GameObject::time;
    animObject[animObject.size()-1]->mesh               = Mesh("./ressources/Shaders/shader.vs", "./ressources/Shaders/shader.fs", "animCube", "./ressources/Models/Primitives/cube.obj", rs, "./ressources/Textures/default.png", 1);
    animObject[animObject.size()-1]->printable          = true;

    bulletLiveTime = 0;
}

void Bullet::BulletCollisionDetection(ResourcesManager& rs)
{
    for (unsigned int i = 0; i < map.size() ; i++)
    {
        Hit hit;
        if (GetFirstCollisionPointBetweenMovingSphereAndStaticBox(map[i]->hitbox, hitbox, Velocity, deltatime, hit))
        {
            Destroy(hit.point, rs);
        }
    }

    for (unsigned int i = 0; i < enemyList->size(); i++)
    {
        Hit hit;
        if (hitbox.CollisionBetweenTwoSphere(hitbox,enemyList[0][i]->hitbox))
        {
            std::cout << "Life : " << enemyList[0][i]->HP << " | damage : " << damage << std::endl;
            enemyList[0][i]->HP -= damage;
            Destroy(hitbox.position, rs);
        }
        
    }
    

    transform.position  = transform.position + Velocity;
    hitbox.position     = transform.position;

    Velocity = Vec3(0,0,0);
}

void Bullet::Move(Mat4& view, Mat4& projection, ResourcesManager& rs)
{   
    Velocity = Velocity +  (transform.forward * speed);
    BulletCollisionDetection(rs);
    transform.worldRef  = Mat4::CreateTransformMatrix(transform.position, Vec3(0.f, 0.f, 0.f), transform.scale);
    Mat4 MVP            = projection * view * transform.worldRef;
    MVP.Transpose();
    mesh.Draw(MVP);
    bulletLiveTime -= deltatime;
}