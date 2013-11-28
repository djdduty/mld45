#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include <Core/State.h>
#include <Level/Level.h>
#include <Utils/ShaderProgram.h>
#include <Renderer/BaseRenderer.h>

namespace MLD {
class MainState : public State
{
private:
    Level*          m_TestLevel;

public:
    MainState();
    ~MainState();

    void Init();
    void DeInit();
    void OnActivate();
    void OnDeactivate();
    void Update(float DeltaTime);
};
}

#endif
