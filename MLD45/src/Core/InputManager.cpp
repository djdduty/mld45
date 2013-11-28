#include <Core/InputManager.h>
#include <Core/Environment.h>

namespace MLD {
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        InputMgr->OnKeyDown(key);

    if(action == GLFW_RELEASE)
        InputMgr->OnKeyUp(key);

    if(action == GLFW_REPEAT)
        InputMgr->OnKeyHeld(key);
}

void MouseButtonCallback(GLFWwindow* Window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
        InputMgr->OnMouseButtonDown(button);

    if(action == GLFW_RELEASE)
        InputMgr->OnMouseButtonUp(button);
}

void MousePosCallback(GLFWwindow* window, double x, double y)
{
    InputMgr->OnMouseMove(x, y);
}

void InitialKeyDownCB(char Key)   {}
void InitialKeyUpCB(char Key)   {}
void InitialKeyHeldCB(char Key)   {}
void InitialMouseMoveCB(double x, double y) {}
void InitialMouseButtonDownCB(int Button)   {}
void InitialMouseButtonUpCB(int Button)     {}


InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::Init(GLFWwindow* Window)
{
    glfwSetKeyCallback(Window, KeyCallback);
    glfwSetCursorPosCallback(Window, MousePosCallback);
    glfwSetMouseButtonCallback(Window, MouseButtonCallback);

    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    SetKeyDown(InitialKeyDownCB);
    SetKeyUp(InitialKeyUpCB);
    SetKeyHeld(InitialKeyHeldCB);
    SetMouseButtonDown(InitialMouseButtonDownCB);
    SetMouseButtonUp(InitialMouseButtonUpCB);
    SetMouseMove(InitialMouseMoveCB);
    m_Window = Window;
}

void InputManager::SetKeyDown(void (*Callback)(char))
{
    KeyDownCB = Callback;
}

void InputManager::SetKeyUp(void (*Callback)(char))
{
    KeyUpCB = Callback;
}

void InputManager::SetKeyHeld(void (*Callback)(char))
{
    KeyHeldCB = Callback;
}

void InputManager::SetMouseButtonDown(void (*Callback)(int))
{
    MouseButtonDownCB = Callback;
}

void InputManager::SetMouseButtonUp(void (*Callback)(int))
{
    MouseButtonUpCB = Callback;
}

void InputManager::SetMouseMove(void (*Callback)(double,double))
{
    MouseMoveCB = Callback;
}

void InputManager::OnKeyDown(char Key)
{
    KeyDownCB(Key);
}

void InputManager::OnKeyUp(char Key)
{
    KeyUpCB(Key);
}

void InputManager::OnKeyHeld(char Key)
{
    KeyHeldCB(Key);
}

void InputManager::OnMouseMove(double x, double y)
{
    MouseMoveCB(x,y);
}
void InputManager::OnMouseButtonDown(int Button)
{
    MouseButtonDownCB(Button);
}

void InputManager::OnMouseButtonUp(int Button)
{
    MouseButtonUpCB(Button);
}

bool InputManager::IsKeyDown(char Key)
{
    if(glfwGetKey(m_Window, Key) == GLFW_PRESS)
        return true;

    return false;
}

bool InputManager::IsMouseButtonDown(int Button)
{
    if(glfwGetMouseButton(m_Window, Button) == GLFW_PRESS)
        return true;

    return false;
}

glm::vec2 InputManager::GetMousePos()
{
    double x,y;
    glfwGetCursorPos(m_Window, &x, &y);
    return glm::vec2(x,y);
}
void InputManager::SetMousePos(glm::vec2 Pos)
{
    glfwSetCursorPos(m_Window, Pos.x, Pos.y);
}
}
