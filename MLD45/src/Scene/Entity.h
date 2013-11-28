#ifndef ENTITY_H
#define ENTITY_H

#include <glm.hpp>
#include <Utils/Sphere.h>
#include <Core/Interfaces.h>
#include <Core/PlatformIncludes.h>
#include <Level/Level.h>
#include <Utils/Image.h>

namespace MLD {
class Scene;

class Entity : public Renderable
{
private:

protected:
    glm::vec3   m_Rotation;
    glm::vec3   m_Position;
    glm::vec3   m_Velocity;
    Sphere*     m_CollisionShape;
    Level*      m_Level;
    Image*      m_Image;
    GLuint      m_Vao,
                m_Vbo;
    Scene*      m_Scene;
    float       m_Health;

public:
    Entity(Level* Lvl, float Size, glm::vec3 Position, const char* ImagePath);
    virtual void Init();
    virtual void UpdatePosition();
    virtual void Update(float DeltaTime);
    virtual void AddVelocity(glm::vec3 Velocity);
    virtual void SetupMesh();
    virtual bool CheckCollision(bool TestX, bool TestZ);
    virtual void PreRender();
    virtual void Render();
    virtual void PostRender();
    virtual void Kill();
    virtual void RemoveHealth(float Amount);
    void Rotate(glm::vec3 Rot);
    bool CollidesWith(Entity* Ent);

    void SetLevel(Level* Lvl)           {m_Level = Lvl;             }
    void SetScene(Scene* Scn)           {m_Scene = Scn;             }
    void SetRotation(glm::vec3 Rot)     {m_Rotation = Rot;          }

    glm::vec3 GetPosition()             {return m_Position;         }
    Sphere*   GetCollisionShape()       {return m_CollisionShape;   }
    glm::mat4 GetTransform();
};
}

#endif
