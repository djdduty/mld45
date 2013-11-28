#include <Scene/Player.h>
#include <Core/Environment.h>

namespace MLD {
Player::Player(Scene* Scn, glm::vec3 Pos, Level* Lvl) : Entity(Lvl, 0.5, Pos, "Data/Images/b3.png")
{
    m_Scene = Scn;
}

Player::~Player()
{}

void Player::Init()
{
    m_Type = ENTITY_RENDERABLE;
    //TODO: Register input, etc
}

void Player::Update(float DeltaTime)
{
    float Speed = 2.0f * DeltaTime;

    if(InputMgr->IsKeyDown('W'))
    {
        AddVelocity(glm::vec3(0,0,-Speed));
    }
    if(InputMgr->IsKeyDown('S'))
    {
        AddVelocity(glm::vec3(0,0,Speed));
    }
    if(InputMgr->IsKeyDown('A'))
    {
        AddVelocity(glm::vec3(-Speed,0,0));
    }
    if(InputMgr->IsKeyDown('D'))
    {
        AddVelocity(glm::vec3(Speed,0,0));
    }
    if(InputMgr->IsKeyDown(GLFW_KEY_SPACE))
    {
        //Shoot();
    }
    UpdatePosition();
}

void Player::Shoot(glm::vec3 Velocity)
{
    //TODO: Create bullet entity, add instance of it to m_Scene when this is called
    //It will test collision against all entities(small levels!) and degrade their health if
    //hit
}
}
