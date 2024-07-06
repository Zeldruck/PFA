#include "my_lib/Enemies.hpp"

Enemy::Enemy(ResourcesManager& rs, const Vec3& position_, const Vec3& scale_, const float& _hitboxRadius, const float& speed_, const int& HP_, const int& ATK_) : Rigidbody(position_, _hitboxRadius, "enemy", "enemy")
{
    activeInHierarchy   = true;
    printable           = true;
    transform.position  = Vec3(0,0,0);
    speed               = speed_;
    HP                  = HP_;
    ATK                 = ATK_;
    transform.scale     = scale_;

    mesh                = Mesh("./ressources/Shaders/shader.vs", "./ressources/Shaders/shader.fs", "Bullet", "./ressources/Models/Primitives/sphere.obj", rs, "./ressources/Textures/red.png");
    transform.worldRef  = Mat4::CreateTransformMatrix(transform.position, Vec3(0.f, 0.f, 0.f), transform.scale);
    transform.position  = position_;
}

Enemy::~Enemy()
{
}

void Enemy::MoveTowardTarget(Vec3 target, float dt)
{
    transform.forward = target - transform.position;
    if(transform.forward.GetMagnitude() > 100)
    {
        transform.forward.Normalize();
        Velocity = Velocity + Vec3(transform.forward.x, 0, transform.forward.z) * speed * dt;
    }
}