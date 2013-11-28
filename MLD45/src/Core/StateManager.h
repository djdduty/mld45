#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <string>
#include <map>

namespace MLD {
class State;

class StateManager
{
public:
    typedef std::map<std::string, State*> AliveStatesMap;

private:
	State* m_CurrentState;
    AliveStatesMap m_AliveStates;

public:
	StateManager(State* State);
	~StateManager();
    void Init();
	void ChangeState(State* State);
    void ChangeState(State* State, std::string StoreStateAliveKey);
    void SetActiveState(std::string Key);
    void SetActiveState(std::string FindKey, std::string StoreStateAliveKey);
	void UpdateState(float DeltaTime);
    void InsertAliveState(std::string Key, State* State);
    State* FindAliveState(std::string Key);

	State* GetState()
	{
		return m_CurrentState;
    }
};
}
#endif
