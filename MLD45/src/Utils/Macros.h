#ifndef MACROS_H
#define MACROS_H

#define Environ         Environment::GetEnv()
#define StateMgr        Environment::GetEnv()->GetStateManager()
#define InputMgr        Environment::GetEnv()->GetInputManager()
#define RenderMgr       Environment::GetEnv()->GetBaseRenderer()

#define WindowWidth     Environment::GetEnv()->GetWindowWidth()
#define WindowHeight    Environment::GetEnv()->GetWindowHeight()

#endif
