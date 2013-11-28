#ifndef SPHERE_H
#define SPHERE_H

#include <glm.hpp>

namespace MLD {
class Sphere;

class Sphere
{
private:
    float       m_Radius;
    glm::vec3 m_Position;

public:
    Sphere(glm::vec3 Pos, float Rad);
    ~Sphere();
    bool CollidesWithSphere(Sphere* Sp);
    void SetPosition(glm::vec3 Pos) {m_Position = Pos; }
    void SetRadius(float Rad)       {m_Radius = Rad;   }
    float GetRadius()               {return m_Radius;  }
    glm::vec3 GetPosition()         {return m_Position;}
};
}

#endif
