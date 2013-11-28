#ifndef BASE_RENDERER_H
#define BASE_RENDERER_H

#include <Utils/ShaderProgram.h>
#include <Core/Interfaces.h>
#include <Scene/Camera.h>
#include <vector>

namespace MLD {
class BaseRenderer
{
public:
    enum UNIFORM_TYPE                                   //Because I am a lazy bastard using arrays for uniforms instead of writing a better shader wrapper, so this avoids uniform confusion later
    {
        PROJECTION_UNIFORM,
        MODELVIEW_UNIFORM,
        SAMPLER_UNIFORM,
        NORMAL_UNIFORM,
        NUM_UNIFORM_TYPE
    };

private:
    std::vector<Renderable*>    m_Renderables;          //List of objects to be rendered every frame
    std::vector<Light*>         m_Lights;               //Lights! \o/
    Camera*                     m_Camera;               //current active camera

    ShaderProgram*              m_DefaultShader,        //Shader for rendering level
                                *m_2DShader;            //Shader for render 2D objects/text

    GLuint                      m_2DUniforms[3],
                                m_DefUniforms[4];

public:
    BaseRenderer();
    ~BaseRenderer();
    void Init();
    void Clear();
    void Update();
    void Render();
    void Setup2DShader();
    void SetupDefaultShader();
    void AddLight(Light* lt);
    void Render2D(Renderable* Ptr);
    void RenderDefault(Renderable* Ptr);
    void AddRenderable(Renderable* rn);

    //setters
    void SetCamera(Camera* Cam);

    //getters
    Camera* GetCamera()         {return m_Camera;}
};
}

#endif
