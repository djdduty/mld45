#ifndef STATE_H
#define STATE_H

#include <string.h>

namespace MLD{
class State
{
private:

public:
    ~State() {DeInit();}
    virtual void Init();
    virtual void DeInit();
    virtual void OnActivate();
    virtual void OnDeactivate();
	virtual void Update(float deltaTime);
};

}
#endif
