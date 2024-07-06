#include "../include/my_lib/Weapon.hpp"

Weapon::Weapon(const int& _ammo, const int& _allAmmo, const float& _bulletSpeed, const float& _bulletScale, const int& _bulletDamage)
{
    ammo            = _ammo;
    allAmmo         = _allAmmo;
    bulletSpeed     = _bulletSpeed;
    bulletDamage    = _bulletDamage;
    bulletScale     = Vec3(_bulletScale, _bulletScale, _bulletScale);
    isShooting      = false;
    reloadTime      = _RELOADTIME;
}

Weapon::~Weapon()
{
    if (bullets.size() > 0)
        bullets.erase(bullets.begin(), bullets.end());
}

void Weapon::Shoot(Vec3 shootPos, Vec3 shootDir, ResourcesManager& rs)
{
    Bullet newBullet = Bullet(rs, bulletScale, shootPos, shootDir, 10, bulletSpeed, 5.f, bulletDamage);
    bullets.push_back(newBullet);
    isShooting = true;
}

void Weapon::BulletsMove(Mat4& view, Mat4& projection, ResourcesManager& rs)
{
    if (bullets.size() == 0)
        return;
    
    for (unsigned int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Move(view, projection, rs);
        if (bullets[i].bulletLiveTime <= 0.f)
        {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}