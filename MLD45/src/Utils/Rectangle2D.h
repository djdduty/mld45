#ifndef RECTANGLE_TWOD_H
#define RECTANGLE_TWOD_H

#include <glm.hpp>

namespace MLD {
class Rectangle2D
{
private:

public:
    glm::vec2 Top;
    glm::vec2 Bot;

    Rectangle2D();
    Rectangle2D(glm::vec2 Pos, glm::vec2 Size);
    ~Rectangle2D();
    void SetPos(glm::vec2 Pos);
    void SetSize(glm::vec2 Sz);
    bool Intersects(Rectangle2D* Rect);
    bool ContainsPoint(glm::vec2 P);
};
}

#endif
