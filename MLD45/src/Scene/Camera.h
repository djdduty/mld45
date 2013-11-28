/*
ATTENTION: This is a shitty, testing purposes only camera! If I made a real one I would have customizable FOV etc etc, and it would use Quats/real rotation
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <Core/PlatformIncludes.h>
#include <Renderer/Frustum.h>

namespace MLD {
class Camera
{
private:

protected:
    glm::mat4 m_Projection;
    glm::mat4 m_Transform;
    glm::vec3 m_Position, m_Rotation;
    Frustum* m_Frustum;

public:
    Camera(glm::vec3 Start);
    ~Camera();
    void Init();
    void Update();
    void MoveCamera(glm::vec3 Move);
    void RotateCamera(glm::vec3 Rot);
    void SetRotation(glm::vec3 Rot)             {m_Rotation = Rot;}
    void SetPosition(glm::vec3 Pos)             {m_Position = Pos;}
    void setProjection(glm::mat4 Projection)    {m_Projection = Projection;}
    glm::mat4 GetTransform();
    glm::mat4 GetProjection()                   {return m_Projection;   }
    Frustum*  GetFrustum()                      {return m_Frustum;      }
    glm::vec3 GetPosition()                     {return m_Position;     }
    glm::vec3 GetRotation()                     {return m_Rotation;     }
};
}

#endif

