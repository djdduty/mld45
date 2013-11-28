#include <Scene/BulletEntity.h>
#include <Scene/Scene.h>

namespace MLD {
Bullet::Bullet(Scene *Scn, glm::vec3 Vel, glm::vec3 Pos, float TimeToLive) : Entity(Scn->GetLevel(), 0.5, Pos, "Data/Images/b2.png")
{
    SetScene(Scn);
    m_BulletVelocity = Vel;
    m_Position = Pos;
    m_LifeTime = TimeToLive;
}

Bullet::~Bullet()
{

}

void Bullet::UpdatePosition()
{
    m_Position += m_Velocity;
    if(m_Scene->CollidesWithEntity(this) != NULL)
    {
        m_Scene->CollidesWithEntity(this)->RemoveHealth(10.0f);
    }
}

void Bullet::Update(float DeltaTime)
{
    UpdatePosition();
    AddVelocity(m_BulletVelocity);

    if(m_LifeTime <= 0.0f)
        Kill();

    m_LifeTime-=DeltaTime;
}

void Bullet::Kill()
{

}
}
