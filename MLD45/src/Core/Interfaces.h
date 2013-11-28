#ifndef INTERFACES_H
#define INTERFACES_H

#include <glm.hpp>

/*
 *Not really filled with interfaces!
 */

namespace MLD {
enum RENDERABLE_TYPE                                    //This makes the system rigid/non-resuable, but since this is a game
{                                                       //not an engine I think it is fine... no time to add full material system.
    DEFAULT_RENDERABLE,
    TWODIM_RENDERABLE,
    ENTITY_RENDERABLE,
    NUM_RENDERABLE_TYPES
};

class Renderable
{
protected:
    glm::mat4 m_Transform;
    RENDERABLE_TYPE m_Type;

public:
    virtual void Init()                 {}
    virtual void PreRender()            {}
    virtual void Render()               =0;
    virtual void PostRender()           {}
    virtual bool IsVisible()            {return true;}
    virtual glm::mat4 GetTransform()    {return m_Transform;}
    virtual RENDERABLE_TYPE GetType()   {return m_Type;}
};


//Light defines
#define ColorRed        glm::vec3(1.0f,0.0f,0.0f)
#define ColorWhite      glm::vec3(1.0f,1.0f,1.0f)
#define ColorGreen      glm::vec3(0.0f,1.0f,0.0f)
#define ColorBlue       glm::vec3(0.0f,0.0f,1.0f)
#define ColorPurple     glm::vec3(1.0f,1.0f,0.0f)
#define ColorCyan       glm::vec3(0.0f,1.0f,1.0f)
//

class Light
{
public:
    glm::vec3 Position;
    glm::vec3 Color;
    float Intensity;

    struct
    {
        float Constant;
        float Linear;
        float Exponential;
    }Attenuation;

    Light()
    {
        Position                = glm::vec3(0.0f,0.0f,0.0f);
        Color                   = ColorWhite;
        Intensity               = 5.0f;
        Attenuation.Constant    = 1.0f;
        Attenuation.Linear      = 0.5f;
        Attenuation.Exponential = 0.5;
    }
};
}

#endif
