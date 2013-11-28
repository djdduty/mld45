#include <States/MainState.h>
#include <Core/PlatformIncludes.h>
#include <Scene/Camera.h>
#include <Core/Environment.h>
#include <Scene/Entity.h>

//other states
#include <States/GameState.h>
//

namespace MLD {
void KeyDownCallback(char Key)
{
    if(Key == 'Q')
        Environ->GetStateManager()->ChangeState(new GameState());
}

void KeyUpCallback(char Key)
{

}

void KeyHeldCallback(char Key)
{

}

MainState::MainState()
{}

MainState::~MainState()
{}

void MainState::Init()
{
    RenderMgr->Clear();

    Camera* camera = new Camera(glm::vec3(-1.0f,-1.0f,20.0f));
    camera->Init();

    m_TestLevel = new Level(5);
    RenderMgr->AddRenderable(m_TestLevel);

    //GlobalCamera = camera;
    RenderMgr->SetCamera(camera);

    Entity* Test = new Entity(m_TestLevel, 1, glm::vec3(-6, 0, 0), "Data/Images/b3.png");
    RenderMgr->AddRenderable(Test);


    InputMgr->SetMousePos(glm::vec2(WindowWidth/2, WindowHeight/2));

    InputMgr->SetKeyDown(KeyDownCallback);
    InputMgr->SetKeyUp(KeyUpCallback);
    InputMgr->SetKeyHeld(KeyHeldCallback);
}

void MainState::DeInit()
{

}

void MainState::OnActivate()
{

}

void MainState::OnDeactivate()
{

}

void MainState::Update(float DeltaTime)
{
    RenderMgr->Render();
}
}
