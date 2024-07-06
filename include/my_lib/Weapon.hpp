#include "vector"
#include "cmath"

#include "Bullet.hpp"

#define _RELOADTIME 2.f
#define _AMMOMAGAZINE 10

class Weapon
{
    public:
        Weapon(const int& _ammo, const int& _allAmmo, const float& _bulletSpeed, const float& _bulletScale, const int& _bulletDamage);
        ~Weapon();

        void Shoot(Vec3 shootPos, Vec3 shootDir, ResourcesManager& rs);
        void BulletsMove(Mat4& view, Mat4& projection, ResourcesManager& rs);

        int ammo, allAmmo, bulletDamage;
        float bulletSpeed, reloadTime;
        Vec3 bulletScale;
        std::vector<Bullet> bullets;
        bool isShooting;
};