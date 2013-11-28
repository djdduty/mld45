#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm.hpp>

namespace MLD {
class Frustum
{
private:
    float m_Frustum[6][4];
protected:

public:
    Frustum();
    ~Frustum();
    void ExtractFrustum(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);  //Sets up the frustum
    float SphereInFrustum(float x, float y, float z, float Radius);         //Returns a float distance >0 if sphere is in frustum, distance can be useful
    bool BoxInFrustum(float x, float y, float z, float Size);               //Returns a bool, true if box is in frustum
};
}

#endif
