#ifndef SCENE_H
#define SCENE_H

#include <Core/PlatformIncludes.h>
#include <Core/Environment.h>
#include <Level/Level.h>
#include <Scene/Player.h>
#include <vector>

namespace MLD {
class Scene
{
private:
    std::vector<Entity*>        m_Entities;
    Level*                      m_Level;

public:
    Scene();
    ~Scene();
    void Init(Level* Lvl);
    void AddEntity(Entity* Ent);
    void Update(float DeltaTime);
    Entity* CollidesWithEntity(Entity* Ent);
    Level*  GetLevel() {return m_Level;}
    void    RemoveEntity(Entity* Ent);
};
}

#endif
