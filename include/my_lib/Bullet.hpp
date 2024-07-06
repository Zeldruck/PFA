#include "LowRenderer/Mesh.h"
#include "Physics/Rigidbody.hpp"
#include "my_lib/Enemies.hpp"

class Bullet : Rigidbody
{
    public:
        Bullet(ResourcesManager& rs, const Vec3& _bulletScale, const Vec3& shootPos, const Vec3& _direction, const float& _hitboxRadius, const float& _speed, const float& _bulletLiveTime, const int& _damage);
        ~Bullet();

        void Move                       (Mat4& view, Mat4& projection, ResourcesManager& rs);
        void BulletCollisionDetection   (ResourcesManager& rs);
        void Destroy                    (const Vec3& hitpoint, ResourcesManager& rs);

        Mat4 bulletMat;
        float bulletLiveTime, speed;
        int damage;
        static std::vector<Enemy*>* enemyList;
};