#include "my_lib/LowRenderer/Camera.h"

Camera::Camera()
{
    phi         = 0.0f;
    theta       = 0.0f;
    speed       = 0.0f;
    sensitivity = 0.0f;
    scWidth     = 0.0f;
    scHeight    = 0.0f;
    sprintSpeed = 0.0f;
}

Camera::Camera(const Vec3& _position, const float& _speed, const float& _sprintSpeed, const float& _sensitivity, const float& _hitboxRadius,  const std::string& _name, const std::string& _tag) : Rigidbody(_position, _hitboxRadius, _name, _tag)
{
    phi         = 1.0f;
    theta       = 0.0f;
    speed       = _speed;
    sprintSpeed = _sprintSpeed;
    sensitivity = _sensitivity;
    HP          = MaxHP         = 10;
}

Camera::~Camera()
{}

Mat4 Camera::CreateViewMatrix()
{
    Mat4 result;
    result.Identity();
    result = result.CreateTransformMatrix(transform.position * -1,Vec3(-phi, -theta + 135, 0.0),Vec3(1.0,1.0,1.0));
    return result ;
}

void Camera::Rotate(const float& xRel, const float& yRel)
{
    phi += -yRel * sensitivity;
    theta += -xRel * sensitivity;

    if(phi > M_PI/2)
        phi = M_PI/2;

    else if(phi < -M_PI/2)
        phi = -M_PI/2;

    /*transform.forward.x = sinf(theta);
    //transform.forward.y = sinf(phi)*2; 
    transform.forward.z = cosf(theta);
    transform.forward.y = sinf(phi);*/

    transform.forward.x = sinf(theta);
    transform.forward.z = cos(theta);
    transform.forward.y = tan(phi);

    //transform.rotation.y = theta;
    
    transform.right = CrossProduct(transform.up, transform.forward);
    transform.right.Normalize();
}

void Camera::Update(GLFWwindow* window, float deltaTime, std::vector<Enemy*> enemyList)
{
    lifetime += deltaTime;
    for(Enemy* mob : enemyList)
    {
        Vec3 DistanceBetweenMobAndPlayer = transform.position - mob->transform.position;
        if( DistanceBetweenMobAndPlayer.GetMagnitude() <= 100 && damageCooldown <= 0 )
        {
            HP -= mob->ATK;
            damageCooldown = 1.5f;
        }
    }
    if ( damageCooldown > 0)
    {
        damageCooldown -= deltaTime;
    }
    Move(window, deltaTime);
}

void Camera::Move(GLFWwindow* window, float dt)
{
    float tempSpeed = speed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        tempSpeed = sprintSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Velocity = Velocity + Vec3(transform.forward.x, 0, transform.forward.z) * tempSpeed * dt;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Velocity = Velocity - Vec3(transform.forward.x, 0, transform.forward.z) * tempSpeed * dt;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
    {   
        Velocity = Velocity + Vec3(transform.right.x, 0, transform.right.z) * tempSpeed * dt; 
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
    {
        Velocity = Velocity - Vec3(transform.right.x, 0, transform.right.z) * tempSpeed * dt;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isGrounded)
    {
        verticalMovement -= 20;
        Velocity = Velocity + transform.up * 7.5;
    }

    /*if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS )
    {
        Velocity = Velocity + transform.up * tempSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS )
    {
        Velocity = Velocity - transform.up * tempSpeed;
    }*/
}

Mat4 Perspective(const float& FoV, const float& aspectRatio, const float& Znear, const float& Zfar)
{
    float range = tanf((FoV * M_PI / 180) / 2.0f) * Znear;
    float sx = (2.0f * Znear) / (range * aspectRatio + range * aspectRatio);
    float sy = Znear / range;
    float sz = -(Zfar + Znear) / (Zfar - Znear);
    float pz = -(2.0f * Zfar * Znear) / (Zfar - Znear);

    Mat4 proj;
    proj.Identity();

    proj.matrix[0] = sx;
    proj.matrix[5] = sy;
    proj.matrix[10] = sz;
    proj.matrix[14] = pz;
    proj.matrix[11] = -1.0f;
    proj.matrix[15] = 0;

    return proj;
}

void Camera::SetPosition(const Vec3& position_)
{
    transform.position = position_;
}

float Camera::GetSensitivity() const
{
    return sensitivity;
}

float Camera::GetSpeed() const
{
    return speed;
}

void Camera::SetSensitivity(const float& sensitivity_)
{
    sensitivity = sensitivity_;
}

void Camera::SetSpeed(const float& speed_)
{
    speed = speed_;
}