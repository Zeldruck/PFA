#ifndef _ENEMIES_HPP_
#define _ENEMIES_HPP_

#include "my_lib/Physics/Rigidbody.hpp"

class Enemy : public Rigidbody
{
    public:
        int HP, ATK;
        float speed;

        Enemy(ResourcesManager& rs, const Vec3& position_, const Vec3& scale_, const float& _hitboxRadius, const float& speed_, const int& HP_, const int& ATK_);
        ~Enemy();

        void MoveTowardTarget(Vec3 target, float dt);
};

#endif