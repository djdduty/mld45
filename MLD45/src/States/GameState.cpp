#include <States/GameState.h>

namespace MLD {

Camera* GlobalCamera;
void MouseMoveCallback(double x, double y)
{
    glm::vec2 MPos;

    MPos = glm::vec2(x,y);
    InputMgr->SetMousePos(glm::vec2(WindowWidth/2, WindowHeight/2));

    glm::vec2 MouseDelta = glm::vec2(WindowWidth/2, WindowHeight/2) - MPos;

    GlobalCamera->RotateCamera(glm::vec3(MouseDelta.y / (10*Environ->GetDeltaTime()*1200), MouseDelta.x / (10*Environ->GetDeltaTime()*1200), 0));
}

GameState::GameState()
{

}

GameState::~GameState()
{

}

void GameState::Init()
{
    GlobalCamera = new Camera(glm::vec3(3,5,7));
    RenderMgr->SetCamera(GlobalCamera);
    GlobalCamera->SetRotation(glm::vec3(-45,0,0));
    InputMgr->SetMouseMove(MouseMoveCallback);
    SetupLevel1();
}

void GameState::Update(float DeltaTime)
{
    GlobalCamera->SetPosition(m_Player->GetPosition());
    m_Player->SetRotation(GlobalCamera->GetRotation());
    RenderMgr->Render();

    m_Scene->Update(DeltaTime);
    RenderMgr->Render();
}

void GameState::SetupLevel1()
{
    RenderMgr->Clear();
    m_Scene = new Scene();

    //Setup the level
    int Layer2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    Level* L1 = new Level(15);

    for(int x = 0; x < L1->GetSize(); x++)
    {
        for(int z = 0; z < L1->GetSize(); z++)
        {
            L1->Set(x,0,z,1);                       //Fill in layer 1(ground)

            int x2 = (z*L1->GetSize())+x;
            L1->Set(x,1,z,Layer2[x2]);              //Fill in layer 2(walls)

            L1->Set(x,2,z,1);                       //Fill in layer 3(ceiling)
        }
    }

    //Setup scene
    m_Scene->Init(L1);

    //Player
    m_Player = new Player(m_Scene, glm::vec3(4,1.5,8),L1);
    //Entity* TP = new Entity(TestLevel, 0.5 ,glm::vec3(1.5,2,2.5),"Data/Images/b3.png");
    m_Player->Init();

    Entity* Ent = new Entity(L1, 0.5, glm::vec3(5,1.5,7), "Data/Images/b3.png");
    m_Scene->AddEntity(Ent);
    m_Scene->AddEntity(m_Player);
}

void GameState::OnActivate()
{

}

void GameState::OnDeactivate()
{

}

void GameState::DeInit()
{

}
}
