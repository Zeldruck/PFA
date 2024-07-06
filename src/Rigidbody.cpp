#include "my_lib/Physics/Rigidbody.hpp"


void Rigidbody::ApplyGravity()
{
    if (verticalMovement < MAX_SPEED)
    {
        verticalMovement += gravity;
    }
    
    Velocity.y -= verticalMovement;
}

void Rigidbody::IsCharacterXWorldCollision()
{
    if (Velocity.GetMagnitude() != 0)
    {
        for (unsigned int i = 0; i < map.size() ; i++)
        {
            Hit hit;
            if (GetFirstCollisionPointBetweenMovingSphereAndStaticBox(map[i]->hitbox, hitbox, Velocity, deltatime, hit))
            {
                Velocity = hit.point - transform.position;
                if (!isGrounded)
                {
                    ApplyGravity();
                }
                
            }
        }
    }

    transform.position = transform.position + Velocity;

    Velocity = Vec3(0,0,0);
    
}

bool Rigidbody::GroundCheck()
{
    Segment seg = Segment(Vec3(hitbox.position.x, hitbox.position.y - ( hitbox.radius + 0.5 ), hitbox.position.z), Vec3(0,-1,0), 1);
    for (unsigned int i = 0; i < map.size() ; i++)
    {
        Hit hit;
        if (IsSegmentIntersectingOrientedBox(seg, map[i]->hitbox, hit))
        {
            return true;
        }
    }

    return false;
}

void Rigidbody::PhysicsCalculation()
{
    isGrounded = GroundCheck();
    if (isGrounded)
    {
        verticalMovement = 0;
    }

    else
    {
        ApplyGravity();
    }

    IsCharacterXWorldCollision();
}

Vec3 Rigidbody::GetDirection()
{
    Vec3 direction = Velocity;
    direction.Normalize();
    return direction;
}

Rigidbody::Rigidbody()
{
    Velocity            = Vec3(0,0,0);
    verticalMovement    = 0;
    isGrounded          = false;
    gravity             = 0;
}

Rigidbody::Rigidbody(const Vec3& _position, const float& _radius, const std::string& _name, const std::string& _tag, const float& _gravity) 
        : GameObject<Sphere>(_position, Vec3(0,0,0), Vec3(1,1,1), _name, _tag) 
{
    Velocity            = Vec3(0,0,0);
    verticalMovement    = 0;
    isGrounded          = false;
    gravity             = _gravity;
    hitbox              = Sphere(_position, _radius);
}

void Rigidbody::Process(const Mat4& modelMat, const Mat4& viewMat , const Mat4& projectionMat)
{
    if (activeInHierarchy)
    {
        Mat4 MVPMatrix;
        MVPMatrix = projectionMat * viewMat * modelMat;
        MVPMatrix.Transpose();

        hitbox.position = transform.position;

        if (tag == "Player" || tag == "enemy")
        {
            PhysicsCalculation();
        }
        

        else
        {
            ApplyGravity();
        }

        if (printable)
        {
            mesh.Draw(MVPMatrix);
        }
    }
}

void Rigidbody::ChildrensProcess(const Mat4& viewMat , const Mat4& projectionMat)
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

Rigidbody::~Rigidbody()
{}