#include <Level/Level.h>
#include <Utils/ShaderProgram.h>

namespace MLD {
Level::Level(int Size) : Renderable()
{
    m_Size = Size;
    m_Blocks = new Block**[m_Size];
    for(int x = 0; x < m_Size; x++)
    {
		m_Blocks[x] = new Block* [m_Size];
        for(int y = 0; y < m_Size; y++)
        {
            m_Blocks[x][y] = new Block[m_Size];
        }
    }
}

Level::~Level()
{}  //TODO

void Level::Init()
{
    m_Transform     = glm::mat4(1.0f);
    m_Type          = DEFAULT_RENDERABLE;
    m_UpdateNeeded  = true;

    m_Image         = new Image();
    m_Image->LoadImage("Data/Images/b2.png");
}

Block* Level::Get(int x, int y, int z)
{
    if(x >= 0 && y >= 0 && z >= 0 && x < m_Size && y < m_Size && z < m_Size)
        return &m_Blocks[x][y][z];
    else
        return 0;
}

void Level::Set(int x, int y, int z, char Type)
{
    m_Blocks[x][y][z].SetType(Type);
    m_UpdateNeeded = true;
}

void Level::Update()
{
    if(m_UpdateNeeded)
    {
        m_ActiveBlockElements = 0;

        int i = 0;

        std::vector<glm::vec3> Vertices, Normals;
        std::vector<glm::vec2> Uvs;

        for(int x = 0; x < m_Size; x++)
        {
            for(int y = 0; y < m_Size; y++)
            {
                for(int z = 0; z < m_Size; z++)
                {
                    if(!m_Blocks[x][y][z].IsActive())
                        continue;

                    CreateBlock(x, y, z, m_Blocks[x][y][z].GetType(), Vertices, Normals, Uvs);
                }
            }
        }

        if(m_ActiveBlockElements == 0)
            return;

        float* Data = new float[m_ActiveBlockElements*8];
        for(int i = 0; i < m_ActiveBlockElements; i++)
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
        glBufferData(GL_ARRAY_BUFFER, ((m_ActiveBlockElements * sizeof(float)) * 8), Data, GL_STATIC_DRAW);

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

        m_UpdateNeeded = false;
    }
}

void Level::CreateBlock(int x, int y, int z, char Type, std::vector<glm::vec3> &Vertices, std::vector<glm::vec3> &Normals, std::vector<glm::vec2> &Uvs)
{
    int i = 0;

    glm::vec3 v1, v2, v3, v4, v5, v6, v7, v8;

    v1 = glm::vec3(x+0,y+0,z+1);
    v2 = glm::vec3(x+1,y+0,z+1);
    v3 = glm::vec3(x+1,y+1,z+1);
    v4 = glm::vec3(x+0,y+1,z+1);
    v5 = glm::vec3(x+1,y+0,z-0);
    v6 = glm::vec3(x+0,y+0,z-0);
    v7 = glm::vec3(x+0,y+1,z-0);
    v8 = glm::vec3(x+1,y+1,z-0);

    Block* Left     = Get(x-1,y+0,z+0);
    Block* Right    = Get(x+1,y+0,z+0);
    Block* Front    = Get(x+0,y+0,z-1);
    Block* Back     = Get(x+0,y+0,z+1);
    Block* Top      = Get(x+0,y+1,z+0);
    Block* Bottom   = Get(x+0,y-1,z+0);

    float TCWSize = (32.0f / 32.0f);
    float TCHSize = (32.0f / 32.0f);
    glm::vec2 TopLeft =     glm::vec2((float)TCWSize, 0);
    glm::vec2 TopRight =    glm::vec2(((float)TCWSize)+TCWSize, 0);
    glm::vec2 BottomLeft =  glm::vec2((float)TCWSize, TCHSize);
    glm::vec2 BottomRight = glm::vec2(((float)TCWSize)+TCWSize, TCHSize);

    if(Type == 10)
    {
        TopLeft =     glm::vec2(0.125f, 0.0f);
        TopRight =    glm::vec2(0.25f, 0.0f);
        BottomLeft =  glm::vec2(0.125f, 1.0f);
        BottomRight = glm::vec2(0.25f, 1.0f);
    }

    if(CullTest(Back) || z == m_Size-1)//had to add the ugly hack(after or) to make it work right... =/
    {
        Vertices.push_back(v1); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,0,1));
        Vertices.push_back(v2); i++; Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(0,0,1));
        Vertices.push_back(v3); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,0,1));

        Vertices.push_back(v1); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,0,1));
        Vertices.push_back(v3); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,0,1));
        Vertices.push_back(v4); i++; Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(0,0,1));
    }
    if(CullTest(Front) || z == 0)//had to add the ugly hack(after or) to make it work right... =/
    {
        Vertices.push_back(v5); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,0,-1));
        Vertices.push_back(v6); i++; Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(0,0,-1));
        Vertices.push_back(v7); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,0,-1));

        Vertices.push_back(v5); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,0,-1));
        Vertices.push_back(v7); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,0,-1));
        Vertices.push_back(v8); i++; Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(0,0,-1));
    }
    if(CullTest(Right) || x == m_Size-1)//had to add the ugly hack(after or) to make it work right... =/
    {
        Vertices.push_back(v2); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(1,0,0));
        Vertices.push_back(v5); i++; Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(1,0,0));
        Vertices.push_back(v8); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(1,0,0));

        Vertices.push_back(v2); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(1,0,0));
        Vertices.push_back(v8); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(1,0,0));
        Vertices.push_back(v3); i++; Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(1,0,0));
    }
    if(CullTest(Left) || x == 0)//had to add the ugly hack(after or) to make it work right... =/
    {
        Vertices.push_back(v6); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(-1,0,0));
        Vertices.push_back(v1); i++; Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(-1,0,0));
        Vertices.push_back(v4); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(-1,0,0));

        Vertices.push_back(v6); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(-1,0,0));
        Vertices.push_back(v4); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(-1,0,0));
        Vertices.push_back(v7); i++; Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(-1,0,0));
    }
    if(CullTest(Top) || y == m_Size-1)//had to add the ugly hack(after or) to make it work right... =/
    {
        Vertices.push_back(v4); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,1,0));
        Vertices.push_back(v3); i++; Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(0,1,0));
        Vertices.push_back(v8); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,1,0));

        Vertices.push_back(v4); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,1,0));
        Vertices.push_back(v8); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,1,0));
        Vertices.push_back(v7); i++; Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(0,1,0));
    }
    if(CullTest(Bottom) || y == 0)//had to add the ugly hack(after or) to make it work right... =/
    {
        Vertices.push_back(v6); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,-1,0));
        Vertices.push_back(v5); i++; Uvs.push_back(BottomLeft) ; Normals.push_back(glm::vec3(0,-1,0));
        Vertices.push_back(v2); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,-1,0));

        Vertices.push_back(v6); i++; Uvs.push_back(BottomRight); Normals.push_back(glm::vec3(0,-1,0));
        Vertices.push_back(v2); i++; Uvs.push_back(TopLeft)    ; Normals.push_back(glm::vec3(0,-1,0));
        Vertices.push_back(v1); i++; Uvs.push_back(TopRight)   ; Normals.push_back(glm::vec3(0,-1,0));
    }

    m_ActiveBlockElements += i;
}

void Level::PreRender()
{
    BindTexture();
}

void Level::Render()
{
    Update();

    if(m_ActiveBlockElements > 0)
    {
        glEnable(GL_CULL_FACE);
        glBindVertexArray(m_Vao);
        glDrawArrays(GL_TRIANGLES,0,m_ActiveBlockElements);
    }
}

void Level::BindTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Image->GetGLTexture());
}

bool Level::TestCollision(glm::vec3 Pos, Rectangle2D* Other, bool TestX, bool TestZ)
{
    //This is some messy ass code right here, I am in a huge drunked tired rush to get it done...
    int bx  = (int)Pos.x;
    int bxr = (int)(Pos.x+0.25f);
    int bxl = (int)(Pos.x-0.25f);
    int by  = (int)Pos.y;
    int bz  = (int)Pos.z;
    int bzf = (int)(Pos.z+0.25f);
    int bzb = (int)(Pos.z-0.25f);

    //top down 2D collision detection(TOP DOWN)
    if(TestX && m_Blocks[bxr][by][bz].IsActive())
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bxr, bz), glm::vec2(bxr+1, bz+1));
        if(Rect->Intersects(Other))
            return true;
    }

    if(TestX && m_Blocks[bxl][by][bz].IsActive())//
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bxl, bz), glm::vec2(bxl+1, bz+1));
        if(Rect->Intersects(Other))
            return true;
    }

    if(TestZ && m_Blocks[bx][by][bzf].IsActive())
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bx, bzf), glm::vec2(bx+1, bzf+1));
        if(Rect->Intersects(Other))
            return true;
    }

    if(TestZ && m_Blocks[bx][by][bzb].IsActive())//
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bx, bzb), glm::vec2(bx+1, bzb+1));
        if(Rect->Intersects(Other))
            return true;
    }

    //Diags to fix corners which is the reason I switched to 2D collision, but now I just realize it was because I was never testing corners...
    //I reall AM tired D:
    if(m_Blocks[bxr][by][bzf].IsActive())
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bxr, bzf), glm::vec2(bxr+1, bzf+1));
        if(Rect->Intersects(Other))
            return true;
    }

    if(m_Blocks[bxl][by][bzf].IsActive())
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bxl, bzf), glm::vec2(bxl+1, bzf+1));
        if(Rect->Intersects(Other))
            return true;
    }

    if(m_Blocks[bxr][by][bzb].IsActive())
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bxr, bzb), glm::vec2(bxr+1, bzb+1));
        if(Rect->Intersects(Other))
            return true;
    }

    if(m_Blocks[bxl][by][bzb].IsActive())
    {
        Rectangle2D* Rect = new Rectangle2D(glm::vec2(bxl, bzb), glm::vec2(bxl+1, bzb+1));
        if(Rect->Intersects(Other))
            return true;
    }



    return false;
}
}
