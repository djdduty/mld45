#include <Utils/Image.h>
#include <iostream>

namespace MLD {
Image::Image()
{

}

Image::~Image()
{

}

void Image::LoadImage(const char* FilePath)
{
    unsigned error = lodepng::decode(m_Image, m_Width, m_Height, FilePath);
    if(error != 0)
    {
      std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
      //return 1;
    }

    size_t u2 = 1; while(u2 < m_Width) u2 *= 2;
    size_t v2 = 1; while(v2 < m_Height) v2 *= 2;
    double u3 = (double)m_Width / u2;
    double v3 = (double)m_Height / v2;

    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < m_Height; y++)
    for(size_t x = 0; x < m_Width; x++)
    for(size_t c = 0; c < 4; c++)
    {
        image2[4 * u2 * y + 4 * x + c] = m_Image[4 * m_Width * y + 4 * x + c];
    }

    glGenTextures(1, &m_GLTex);
    glBindTexture(GL_TEXTURE_2D, m_GLTex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

    m_Image = image2;
    m_Width = u2;
    m_Height = v2;
}

GLuint Image::GetGLTexture()
{
    return m_GLTex;
}

void Image::LoadImage2(const char* FilePath)
{
    /*std::vector rawImage;

        lodePNG::loadFile( rawImage, FilePath );
        lodePNG::Decoder decoder;
        std::vector image;

        decoder.decode( image, rawImage.empty() ? 0 : &rawImage[0],(unsigned)rawImage.size() );

        int sizex = decoder.getWidth();
        int sizey = decoder.getHeight();
        imageSize = image.size();
        colorDepth = decoder.getBpp();
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        pixmap = new GLubyte[imageSize];

        //
        // Flip and invert the PNG image since OpenGL likes to load everything
        // backwards from what is considered normal!
        //
        unsigned char *imagePtr = &image[0];
        int halfTheHeightInPixels = decoder.getHeight() / 2;
        int heightInPixels = decoder.getHeight();

        // Assuming RGBA for 4 components per pixel.
        int numColorComponents = 4;
        // Assuming each color component is an unsigned char.
        int widthInChars = decoder.getWidth() * numColorComponents;
        unsigned char *top = NULL;

        unsigned char *bottom = NULL;
        unsigned char temp = 0;
        for( int h = 0; h < halfTheHeightInPixels; ++h )

        {

            top = imagePtr + h * widthInChars;
            bottom = imagePtr + (heightInPixels - h - 1) * widthInChars;
            for( int w = 0; w < widthInChars; ++w )
            {

                // Swap the chars around.
                temp = *top;
                *top = *bottom;
                *bottom = temp;
                ++top;
                ++bottom;
            }
        }

        unsigned int c=0;
        for (unsigned int x = 0; x < size.x; x++)
        for (unsigned int y=0; y<size.y; y++)
            for (unsigned int co=0; co<numColorComponents; co++)
                ((GLubyte*)pixmap)[c++]=image[c];

        glGenTextures(1, &m_GLTex);
        glBindTexture(GL_TEXTURE_2D, m_GLTex);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagePtr);
        m_Width = sizex; m_Height = sizey;*/
}
}
