#ifndef IMAGE_H
#define IMAGE_H

#include <Utils/Lodepng.h>
#include <Core/PlatformIncludes.h>

namespace MLD {
class Image
{
private:
    const char* FilePath;
    std::vector<unsigned char> m_Image;
    unsigned m_Width, m_Height;
    GLuint m_GLTex;

public:
    Image();
    ~Image();
    void LoadImage(const char* FilePath);
    void LoadImage2(const char* FilePath);//testing purposes
    GLuint GetGLTexture();
    unsigned GetWidth() {return m_Width;}
    unsigned GetHeight() {return m_Height;}
};
}

#endif
