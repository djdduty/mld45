#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Core/State.h>
#include <Level/Level.h>
#include <Scene/Scene.h>

namespace MLD {
class GameState : public State
{
private:
    Scene*          m_Scene;
    Player*         m_Player;

public:
    GameState();
    ~GameState();

    void Init();
    void DeInit();
    void OnActivate();
    void OnDeactivate();
    void Update(float DeltaTime);

    void SetupLevel1();
};
}

#endif
