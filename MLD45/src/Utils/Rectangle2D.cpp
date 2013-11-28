#include <Utils/Rectangle2D.h>

namespace MLD {
Rectangle2D::Rectangle2D()
{
    Top = glm::vec2(0,0);
    Bot = glm::vec2(0,0);
}

Rectangle2D::Rectangle2D(glm::vec2 Pos, glm::vec2 Size)
{
    Top = Pos;
    Bot = Pos + Size;
}

void Rectangle2D::SetPos(glm::vec2 Pos)
{
    Top = Pos;
}

void Rectangle2D::SetSize(glm::vec2 Sz)
{
    Bot = Top + Sz;
}

bool Rectangle2D::Intersects(Rectangle2D* Other)
{
    return !(Bot.x <= Other->Top.x ||
             Top.x >= Other->Bot.x ||
             Bot.y <= Other->Top.y ||
             Top.y >= Other->Bot.y);
}

bool Rectangle2D::ContainsPoint(glm::vec2 P)
{
    return (P.x > Top.x) && (P.x < Bot.x) && (P.y > Top.y) && (P.y < Bot.y);
}
}
