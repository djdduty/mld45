#include <Core/Environment.h>
#include <Scene/Camera.h>
#include <glm.hpp>

namespace MLD {
Camera::Camera(glm::vec3 Start)
{
    m_Position = Start;
    m_Rotation = glm::vec3(0.0f,0.0f,0.0f);
    m_Transform = glm::mat4(1.0f);
    m_Projection = glm::perspective(45.0f, (float)WindowWidth/(float)WindowHeight, 0.1f, 1000.0f);
    m_Frustum = new Frustum();
}
void Camera::Init()
{
    m_Frustum->ExtractFrustum(GetTransform(), GetProjection());
}

Camera::~Camera()
{

}

void Camera::Update()
{
    m_Frustum->ExtractFrustum(GetTransform(), GetProjection());
}

void Camera::MoveCamera(glm::vec3 Move) //This function is a bucket of shit, the most terrible code you will ever see....
{
    m_Position += Move;
}

void Camera::RotateCamera(glm::vec3 Rot)
{
    m_Rotation += glm::vec3(0, Rot.y, Rot.z);
    
    m_Rotation += glm::vec3(Rot.x, 0, 0);
    
    if(m_Rotation.x > 90)
        m_Rotation.x = 89.9;
    
    if(m_Rotation.x < -90)
        m_Rotation.x = -89.9;
    
    m_Transform = (glm::rotate(glm::mat4(1.0f), Rot.x, glm::vec3(1,0,0)) * glm::rotate(glm::mat4(1.0f), Rot.y, glm::vec3(0,1,0))) * m_Transform;
}

glm::mat4 Camera::GetTransform()
{
    glm::mat4 m4 = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0,1,0)) * glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1,0,0));
    return glm::inverse(m4);
}
}

