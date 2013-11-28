#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Core/PlatformIncludes.h>
#include <glm.hpp>

namespace MLD {
class InputManager
{
private:
    void (*KeyDownCB)(char);                    //I probably went about this all wrong...
    void (*KeyUpCB)(char);
    void (*KeyHeldCB)(char);
    void (*MouseMoveCB)(double,double);
    void (*MouseButtonDownCB)(int);
    void (*MouseButtonUpCB)(int);
    GLFWwindow* m_Window;

public:
    InputManager();
    ~InputManager();
    void Init(GLFWwindow* Window);

    void SetKeyDown(void (*Callback)(char));
    void SetKeyUp(void (*Callback)(char));
    void SetKeyHeld(void (*Callback)(char));

    void SetMouseMove(void (*Callback)(double,double));
    void SetMouseButtonDown(void (*Callback)(int));
    void SetMouseButtonUp(void (*Callback)(int));

    void OnKeyDown(char Key);
    void OnKeyUp(char Key);
    void OnKeyHeld(char Key);
    void OnMouseMove(double x, double y);
    void OnMouseButtonDown(int Button);
    void OnMouseButtonUp(int Button);

    bool IsKeyDown(char Key);
    void SetMousePos(glm::vec2 Pos);
    bool IsMouseButtonDown(int Button);
    glm::vec2 GetMousePos();
};
}

#endif
