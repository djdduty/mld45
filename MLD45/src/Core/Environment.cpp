#include <Core/Environment.h>

namespace MLD {


Environment::Environment() : m_InputManager(new InputManager()),
                             m_Renderer(new BaseRenderer())
{

}

Environment::~Environment()
{
    delete m_StateManager;
}

void Environment::Init(GLFWwindow* Window, State* StartState)
{
    m_Renderer->Init();
    m_StateManager = new StateManager(StartState);
    m_InputManager->Init(Window);
    m_Window = Window;
    
    glfwGetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);

    m_StateManager->Init();
}

void Environment::Update(float DeltaTime)
{
    glfwGetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);

    m_DeltaTime = DeltaTime;
    m_Renderer->Update();
    m_StateManager->UpdateState(DeltaTime);
}
}
