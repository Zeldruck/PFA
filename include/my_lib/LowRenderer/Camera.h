#if !defined(CAMERA_H)
#define CAMERA_H

#include "my_lib/Core/Maths/Mat4.h"
#include "my_lib/Core/Maths/Sphere.hpp"
#include "my_lib/Physics/Rigidbody.hpp"
#include <GLFW/glfw3.h>
#include "my_lib/Enemies.hpp"
#include <vector>

class Camera : public Rigidbody
{
public:
    int         MaxHP,
                HP;
    float       scWidth,
                scHeight,
                phi,
                theta,
                speed,
                sprintSpeed,
                sensitivity,
                damageCooldown = 1.5f,
                lifetime=0;
    double      xMousePos, 
                yMousePos;
    
    Camera                  ();
    Camera                  (const Vec3& _position, const float& _speed, const float& _sprintSpeed, const float& _sensitivity, const float& _hitboxRadius, const std::string& _name = "", const std::string& _tag = "");
    ~Camera                 ();
    Mat4 CreateViewMatrix   ();
    void Update             (GLFWwindow* window, float dt, std::vector<Enemy*> enemyList);
    void Rotate             (const float& xRel, const float& yRel);
    void Move               (GLFWwindow* window, float dt);
    void SetPosition        (const Vec3& position);
    float GetSensitivity    () const;
    float GetSpeed          () const;
    void SetSensitivity     (const float& sensitivity);
    void SetSpeed           (const float& speed);
};

Mat4 Perspective(const float&, const float&, const float&, const float&); 

#endif // CAMERA_H
