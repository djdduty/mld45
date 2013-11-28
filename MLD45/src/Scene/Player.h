#ifndef PLAYER_H
#define PLAYER_H

#include <Scene/Entity.h>
#include <glm.hpp>

namespace MLD {
class Scene;

class Player : public Entity
{
private:
    Scene*    m_Scene;

public:
    Player(Scene* Scn, glm::vec3 Pos, Level* Lvl);
    ~Player();
    void Init();
    void Update(float DeltaTime);
    void Shoot(glm::vec3 Velocity);
};
}

#endif
