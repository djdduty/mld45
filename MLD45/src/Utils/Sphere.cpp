#include <Utils/Sphere.h>

namespace MLD {
Sphere::Sphere(glm::vec3 Pos, float Rad)
{
    m_Position = Pos;
    m_Radius = Rad;
}

Sphere::~Sphere()
{}

bool Sphere::CollidesWithSphere(Sphere* Sp)
{
    float s1x = m_Position.x;
    float s1y = m_Position.y;
    float s1z = m_Position.z;
    float s1Radius = m_Radius;

    float s2x = Sp->GetPosition().x;
    float s2y = Sp->GetPosition().y;
    float s2z = Sp->GetPosition().z;
    float s2Radius = Sp->GetRadius();

    float d = sqrt(((s1x - s2x) * (s1x - s2x)) + ((s1y - s2y) * (s1y - s2y)) + ((s1z - s2z) * (s1z - s2z)));

    if(d > (s1Radius + s2Radius))
    {
            return false;
    }
    printf("Collision happened, %d :\n",d);
    return true;
}
}
