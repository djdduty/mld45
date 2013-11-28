#include <Scene/Entity.h>
#include <gtc/matrix_transform.hpp>
#include <Utils/Rectangle2D.h>
#include <Utils/ShaderProgram.h>
#include <Scene/Scene.h>

namespace MLD {
Entity::Entity(Level* Lvl, float Size, glm::vec3 Position, const char* ImagePath)
{
    m_Image = new Image();
    m_Image->LoadImage(ImagePath);

    m_Type = ENTITY_RENDERABLE;

    m_Level = Lvl;
    m_Position = Position;
    m_Velocity = glm::vec3(0.0f,0.0f,0.0f);
    m_CollisionShape = new Sphere(Position, Size/2);
    m_Transform = glm::translate(glm::mat4(1.0f), m_Position);

    SetupMesh();
}

void Entity::Init()
{

}

void Entity::Update(float DeltaTime)
{
    UpdatePosition();
}

void Entity::UpdatePosition()
{
    m_Position.x += m_Velocity.x;
    if(CheckCollision(true, false))
    {
        m_Position.x -= m_Velocity.x;
    }

    m_Position.z += m_Velocity.z;
    if(CheckCollision(false, true))
    {
        m_Position.z -= m_Velocity.z;
    }

    m_Velocity = glm::vec3(0,0,0);
    m_CollisionShape->SetPosition(m_Position);
}

bool Entity::CheckCollision(bool TestX, bool TestZ)
{
    float Size = m_CollisionShape->GetRadius();
    Rectangle2D* Rect = new Rectangle2D(glm::vec2(m_Position.x, m_Position.z), glm::vec2(m_Position.x+Size,m_Position.x+Size));
    if(m_Level->TestCollision(m_Position, Rect, TestX, TestZ))
        return true;

    return false;
}

void Entity::AddVelocity(glm::vec3 Velocity)
{  
    glm::mat4 m4 = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0,1,0)) * glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1,0,0)) * glm::translate(glm::mat4(1.0f), Velocity);
    glm::vec3 V2 = glm::vec3(m4[3][0], m4[3][1], m4[3][2]);
    m_Velocity += V2;
}

void Entity::PreRender()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Image->GetGLTexture());
}

void Entity::Render()
{
    glDisable(GL_CULL_FACE);
    glBindVertexArray(m_Vao);
    glDrawArrays(GL_TRIANGLES,0,6);
    glDisable(GL_CULL_FACE);
}

void Entity::PostRender()
{

}

bool Entity::CollidesWith(Entity *Ent)
{
    return m_CollisionShape->CollidesWithSphere(Ent->GetCollisionShape());
}

void Entity::SetupMesh()
{
    std::vector<glm::vec3> Vertices, Normals;
    std::vector<glm::vec2> Uvs;

    float w = m_CollisionShape->GetRadius();
    glm::vec3 v1 = glm::vec3(-w,-w,0);
    glm::vec3 v2 = glm::vec3( w,-w,0);
    glm::vec3 v3 = glm::vec3( w, w,0);
    glm::vec3 v4 = glm::vec3(-w, w,0);

    glm::vec2 TopLeft =     glm::vec2(0, 0);
    glm::vec2 TopRight =    glm::vec2(1, 0);
    glm::vec2 BottomLeft =  glm::vec2(0, 1);
    glm::vec2 BottomRight = glm::vec2(1, 1);

    Vertices.push_back(v1); Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,0,1));
    Vertices.push_back(v2); Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(0,0,1));
    Vertices.push_back(v3); Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,0,1));

    Vertices.push_back(v1); Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,0,1));
    Vertices.push_back(v3); Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,0,1));
    Vertices.push_back(v4); Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(0,0,1));

    float* Data = new float[6*8];
    for(int i = 0; i < 6; i++)
    {
        glm::vec3 vert;
        glm::vec3 norm;
        glm::vec2 uv;
        vert = Vertices[i];
        norm = Normals[i];
        uv = Uvs[i];
        Data[i*8+0] = vert.x;
        Data[i*8+1] = vert.y;
        Data[i*8+2] = vert.z;
        Data[i*8+3] = norm.x;
        Data[i*8+4] = norm.y;
        Data[i*8+5] = norm.z;
        Data[i*8+6] = uv.x;
        Data[i*8+7] = uv.y;
    }

    glGenVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
    glGenBuffers(1, &m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, ((6 * sizeof(float)) * 8), Data, GL_STATIC_DRAW);

    glBindVertexArray(m_Vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glEnableVertexAttribArray(ShaderProgram::VERTEX_COORD_ATTRIB);
    glVertexAttribPointer(ShaderProgram::VERTEX_COORD_ATTRIB, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

    glEnableVertexAttribArray(ShaderProgram::NORMAL_ATTRIB);
    glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(3*sizeof(GLfloat)));

    glEnableVertexAttribArray(ShaderProgram::TEXTURE_COORD_ATTRIB);
    glVertexAttribPointer(ShaderProgram::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(6*sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Vertices.clear();
    Normals.clear();
    Uvs.clear();
    delete[] Data;
}

void Entity::Rotate(glm::vec3 Rot)
{
    m_Rotation += glm::vec3(Rot.y, Rot.y, Rot.z);

    if(m_Rotation.x > 90)
        m_Rotation.x = 89.9;

    if(m_Rotation.x < -90)
        m_Rotation.x = -89.9;
}

glm::mat4 Entity::GetTransform()
{
    return glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0,1,0)) * glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1,0,0));
}

void Entity::Kill()
{
    m_Scene->RemoveEntity(this);
}

void Entity::RemoveHealth(float Amount)
{
    m_Health -= Amount;
    if(m_Health <= 0.0f)
        Kill();
}
}
