#include <Core/StateManager.h>
#include <Core/State.h>
#include <iostream>

namespace MLD {
StateManager::StateManager(State* state) 
{
	m_CurrentState = state;
}

StateManager::~StateManager()
{
    delete m_CurrentState;
}

void StateManager::Init()
{
    //TmpHolder->Init();
	m_CurrentState->Init();
}

void StateManager::ChangeState(State* state) 
{
    State* OldState = m_CurrentState;

	m_CurrentState = state;
	m_CurrentState->Init();

    delete OldState;
}


void StateManager::ChangeState(State* state, std::string Key) 
{
    State* OldState = m_CurrentState;

	m_CurrentState = state;
	m_CurrentState->Init();

    OldState->OnDeactivate();
    InsertAliveState(Key, OldState);
}

void StateManager::SetActiveState(std::string Key)
{
    State* AliveState = FindAliveState(Key);

    if(AliveState != NULL)
    {
        State* OldState = m_CurrentState;

        m_CurrentState = AliveState;
        m_CurrentState->OnActivate();
        
        delete OldState;
    }
    else
    {
        //error out
    }
}

void StateManager::SetActiveState(std::string Key, std::string SaveKey)
{
    State* AliveState = FindAliveState(Key);

    if(AliveState != NULL)
    {
        State* OldState = m_CurrentState;

        m_CurrentState = AliveState;
        m_CurrentState->OnActivate();
        
        OldState->OnDeactivate();
        InsertAliveState(SaveKey, OldState);
    }
    else
    {
        //error out
    }
}

State* StateManager::FindAliveState(std::string Key)
{
    for(AliveStatesMap::iterator it = m_AliveStates.begin(); it != m_AliveStates.end(); it++)
    {
        if(it->first == Key)
        {
            return it->second;
        }
        else
            return NULL;
        //error out
    }
}

void StateManager::InsertAliveState(std::string Key, State* State)
{
    m_AliveStates.insert(std::make_pair(Key, State));
}

void StateManager::UpdateState(float DeltaTime) 
{
    m_CurrentState->Update(DeltaTime);
}

//------------------------------------------------------------------------------------------------------------------------//

void State::Init()
{}

void State::DeInit()
{}

void State::OnActivate()
{}

void State::OnDeactivate()
{}

void State::Update(float DeltaTime)
{}
}
