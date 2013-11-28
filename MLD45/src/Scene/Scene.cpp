#include <Scene/Scene.h>
#include <algorithm>

namespace MLD {
Scene::Scene()
{

}

Scene::~Scene()
{
    delete m_Level;
    for(int i = 0; i < m_Entities.size(); i++)
        delete m_Entities[i];
}

void Scene::Init(Level* Lvl)
{
    m_Level = Lvl;
    RenderMgr->AddRenderable(Lvl);
}

void Scene::Update(float DeltaTime)
{
    for(int i = 0; i < m_Entities.size(); i++)
        m_Entities[i]->Update(DeltaTime);
}

void Scene::AddEntity(Entity *Ent)
{
    m_Entities.push_back(Ent);
    Ent->SetScene(this);
    Ent->SetLevel(m_Level);
    RenderMgr->AddRenderable(Ent);
}

Entity* Scene::CollidesWithEntity(Entity *Ent)
{
    for(int i = 0; i < m_Entities.size(); i++)
    {
        if(Ent->CollidesWith(m_Entities[i]) && m_Entities[i] != Ent)
            return m_Entities[i];
    }

    return NULL;
}

void Scene::RemoveEntity(Entity *Ent)
{
    std::vector<Entity*>::iterator It = std::find(m_Entities.begin(), m_Entities.end(), Ent);
    if(It != m_Entities.end())
        m_Entities.erase(It);
}
}
