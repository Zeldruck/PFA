#if !defined(RIGIDBODY_HPP)
#define RIGIDBODY_HPP

#define MAX_SPEED 30

#include "my_lib/Core/DataStructure/GameObject.hpp"
#include "my_lib/Core/Maths/Collision.hpp"

class Rigidbody : public GameObject<Sphere>
{
public:
    float   verticalMovement;
    Vec3    Velocity;
    bool    isGrounded;
    float   gravity;

    Rigidbody                           ();
    Rigidbody                           (const Vec3& _position, const float& _radius, const std::string& _name = "", const std::string& _tag = "", const float& _gravity = 0);
    ~Rigidbody                          ();
    void Process                        (const Mat4& modelMat, const Mat4& viewMat , const Mat4& projectionMat) override;
    void ChildrensProcess               (const Mat4& viewMat , const Mat4& projectionMat) override;
    void IsCharacterXWorldCollision     ();
    void ApplyGravity                   ();
    bool GroundCheck                    ();
    void PhysicsCalculation             ();
    Vec3 GetDirection                   ();
};

#endif // RIGIDBODY_HPP 
