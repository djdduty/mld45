#ifndef BULLET_ENTITY_H
#define BULLET_ENTITY_H

#include <Scene/Entity.h>
#include <glm.hpp>

namespace MLD {
class Bullet : public Entity
{
private:
    glm::vec3   m_BulletVelocity;
    float       m_LifeTime;

public:
    Bullet(Scene* Scn, glm::vec3 Vel, glm::vec3 Pos, float TimeToLive);
    ~Bullet();
    void Kill();
    void UpdatePosition();
    void Update(float DeltaTime);
};
}

#endif
