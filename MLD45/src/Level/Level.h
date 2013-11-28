#ifndef LEVEL_H
#define LEVEL_H

#define CullTest(Side) (!Side || (Side && !Side->IsActive()))   //seems to be broken? =/
#define SPRITE_SIZE 32
#define IMAGE_WIDTH 256     //temp
#define IMAGE_HEIGHT 32     //temp

#include <Level/Block.h>
#include <Core/PlatformIncludes.h>
#include <Utils/Rectangle2D.h>
#include <Core/Interfaces.h>
#include <Utils/Image.h>
#include <Utils/Sphere.h>
#include <vector>
#include <glm.hpp>

namespace MLD {
class Level : public Renderable
{
public:
    enum BLOCK_TYPE
    {
        BLOCK_TYPE_INACTIVE,
        BLOCK_TYPE_BRICK,
        BLOCK_TYPE_GRASS,
        BLOCK_TYPE_STONE,
        BLOCK_TYPE_HEDGE,
        BLOCK_TYPE_VINE,
        NUM_BLOCK_TYPES
    };

private:
    Block*** m_Blocks;
    bool m_UpdateNeeded;
    GLuint m_Vbo, m_Vao;
    int m_Size, m_ActiveBlockElements;
    Image* m_Image;

public:
    Level(int Size);
    ~Level();
    void Init();
    void Update();
    void PreRender();
    void Render();
    void CreateBlock(int x, int y, int z, char Type, std::vector<glm::vec3> &Vertices, std::vector<glm::vec3> &Normals, std::vector<glm::vec2> &Uvs);
    bool TestCollision(glm::vec3 Pos, Rectangle2D* Other, bool TestX, bool TestZ);

    //Setters
    void Set(int x, int y, int z, char Type);
    void SetNeedsUpdate()   {m_UpdateNeeded = true;}
    //

    void BindTexture();

    //Getters
    Block* Get(int x, int y, int z);
    int GetSize()           {return m_Size;}
    //
};
}

#endif
