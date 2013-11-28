#include <Renderer/BaseRenderer.h>

namespace MLD {
BaseRenderer::BaseRenderer()
{}

BaseRenderer::~BaseRenderer()
{

}

void BaseRenderer::Init()
{
    Setup2DShader();
    SetupDefaultShader();
}

void BaseRenderer::Update()
{
    m_Camera->Update();
}

void BaseRenderer::Render()
{
    glEnable(GL_DEPTH_TEST);

    for(int i = 0; i < m_Renderables.size(); i++)
    {
        Renderable* Ptr = m_Renderables[i];
        if(Ptr->GetType() == DEFAULT_RENDERABLE || Ptr->GetType() == ENTITY_RENDERABLE)
            RenderDefault(Ptr);

        if(Ptr->GetType() == TWODIM_RENDERABLE)
            Render2D(Ptr);
    }

    glDisable(GL_DEPTH_TEST);
}

void BaseRenderer::Render2D(Renderable* Ptr)
{

}

void BaseRenderer::RenderDefault(Renderable* Ptr)
{
    glUseProgram(m_DefaultShader->getProgramIndex());                                             //Bind program

    glm::mat4 ModelView     = m_Camera->GetTransform() * Ptr->GetTransform();
    if(Ptr->GetType() == ENTITY_RENDERABLE)
    {
        ModelView[0][0] = 1.0f;
        ModelView[0][1] = 0.0f;
        ModelView[0][2] = 0.0f;

        //ModelView[1][0] = 0.0f;
        //ModelView[1][1] = 1.0f;
        //ModelView[1][2] = 0.0f;

        ModelView[2][0] = 0.0f;
        ModelView[2][1] = 0.0f;
        ModelView[2][2] = 1.0f;
    }
    //Matrices
    glm::mat4 Projection    = m_Camera->GetProjection();
    glm::mat3 NormalMat     = glm::transpose(glm::inverse(glm::mat3(ModelView)));
    //

    //Uniforms
    Ptr->PreRender();
    glUniform1f(m_DefUniforms[SAMPLER_UNIFORM], 0);
    glUniformMatrix3fv(m_DefUniforms[NORMAL_UNIFORM], 1, GL_FALSE, &NormalMat[0][0]);
    glUniformMatrix4fv(m_DefUniforms[MODELVIEW_UNIFORM], 1, GL_FALSE, &ModelView[0][0]);
    glUniformMatrix4fv(m_DefUniforms[PROJECTION_UNIFORM], 1, GL_FALSE, &Projection[0][0]);
    //

    //Draw call
    Ptr->Render();
    Ptr->PostRender();
    //

    glUseProgram(0);                                                                            //Unbind program
}

void BaseRenderer::Setup2DShader()
{

}

void BaseRenderer::SetupDefaultShader()
{
    m_DefaultShader = new ShaderProgram();
    m_DefaultShader->init();
    m_DefaultShader->loadShader(ShaderProgram::VERTEX_SHADER, "Data/Shaders/BlockShader.vert");
    m_DefaultShader->loadShader(ShaderProgram::FRAGMENT_SHADER, "Data/Shaders/BlockShader.frag");

    printf(m_DefaultShader->getAllInfoLogs().c_str());

    glUseProgram(m_DefaultShader->getProgramIndex());

    m_DefaultShader->setProgramOutput(0, "outputF");
    m_DefaultShader->setVertexAttribName(ShaderProgram::VERTEX_COORD_ATTRIB, "Vertex");
    m_DefaultShader->setVertexAttribName(ShaderProgram::TEXTURE_COORD_ATTRIB, "Uv");
    m_DefaultShader->setVertexAttribName(ShaderProgram::NORMAL_ATTRIB, "Normal");

    m_DefaultShader->prepareProgram();
    m_DefUniforms[PROJECTION_UNIFORM] = glGetUniformLocation(m_DefaultShader->getProgramIndex(), "ProjectionMatrix");
    m_DefUniforms[MODELVIEW_UNIFORM] = glGetUniformLocation(m_DefaultShader->getProgramIndex(), "ModelViewMatrix");
    m_DefUniforms[SAMPLER_UNIFORM] = glGetUniformLocation(m_DefaultShader->getProgramIndex(), "Texture");
    m_DefUniforms[NORMAL_UNIFORM] = glGetUniformLocation(m_DefaultShader->getProgramIndex(), "NormalMatrix");
    glUseProgram(0);
}

void BaseRenderer::AddLight(Light* lt)
{
    m_Lights.push_back(lt);
}

void BaseRenderer::AddRenderable(Renderable* rn)
{
    m_Renderables.push_back(rn);
	rn->Init();
}

void BaseRenderer::Clear()
{
    m_Renderables.clear();
    m_Lights.clear();
}

void BaseRenderer::SetCamera(Camera* Cam) 
{
	m_Camera = Cam;
}
}
