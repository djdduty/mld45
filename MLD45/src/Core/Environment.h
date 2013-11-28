#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <Core/PlatformIncludes.h>
#include <Renderer/BaseRenderer.h>
#include <Core/InputManager.h>
#include <Core/StateManager.h>
#include <Utils/Macros.h>
#include <Core/State.h>

namespace MLD {
class Environment
{
private:
    Environment();

protected:
    StateManager*   m_StateManager;
    InputManager*   m_InputManager;
    GLFWwindow*     m_Window;
    BaseRenderer*   m_Renderer;

    float m_DeltaTime;
    int m_WindowWidth, m_WindowHeight;

    //Input
    

public:
    ~Environment();
    static Environment  *GetEnv() { static Environment *gEnv = new Environment(); return gEnv; }

    void Init(GLFWwindow* Window, State* StartState);
    void Update(float DeltaTime);

    BaseRenderer*       GetBaseRenderer()       const {return m_Renderer;       }
    StateManager*       GetStateManager()       const {return m_StateManager;   }
    InputManager*       GetInputManager()       const {return m_InputManager;   }
    int                 GetWindowWidth()        {return m_WindowWidth;          }
    int                 GetWindowHeight()       {return m_WindowHeight;         }
    float               GetDeltaTime()          {return m_DeltaTime;            }
    GLFWwindow*         GetGLFWWindow()         {return m_Window;               }
};
}

#endif
