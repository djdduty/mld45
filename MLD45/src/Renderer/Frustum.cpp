#include <Renderer/Frustum.h>

namespace MLD {
Frustum::Frustum()
{}

Frustum::~Frustum()
{

}
float Frustum::SphereInFrustum(float x, float y, float z, float radius)
{
    int p;
    float d;

    for(p = 0; p < 6; p++)
    {
        d = m_Frustum[p][0] * x + m_Frustum[p][1] * y + m_Frustum[p][2] * z + m_Frustum[p][3];
        if( d <= -radius )
           return 0;
    }

    return d + radius;
}

bool Frustum::BoxInFrustum(float x, float y, float z, float size)
{
   int p;

   for( p = 0; p < 6; p++ )
   {
      if( m_Frustum[p][0] * (x - size) + m_Frustum[p][1] * (y - size) + m_Frustum[p][2] * (z - size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x + size) + m_Frustum[p][1] * (y - size) + m_Frustum[p][2] * (z - size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x - size) + m_Frustum[p][1] * (y + size) + m_Frustum[p][2] * (z - size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x + size) + m_Frustum[p][1] * (y + size) + m_Frustum[p][2] * (z - size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x - size) + m_Frustum[p][1] * (y - size) + m_Frustum[p][2] * (z + size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x + size) + m_Frustum[p][1] * (y - size) + m_Frustum[p][2] * (z + size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x - size) + m_Frustum[p][1] * (y + size) + m_Frustum[p][2] * (z + size) + m_Frustum[p][3] > 0 )
         continue;
      if( m_Frustum[p][0] * (x + size) + m_Frustum[p][1] * (y + size) + m_Frustum[p][2] * (z + size) + m_Frustum[p][3] > 0 )
         continue;
      return false;
   }
   return true;
}

void Frustum::ExtractFrustum(glm::mat4 Mv, glm::mat4 Projection)
{
    float proj[] = {
           Projection[0][0], Projection[0][1], Projection[0][2], Projection[0][3],
           Projection[1][0], Projection[1][1], Projection[1][2], Projection[1][3],
           Projection[2][0], Projection[2][1], Projection[2][2], Projection[2][3],
           Projection[3][0], Projection[3][1], Projection[3][2], Projection[3][3]
       };

       float modl[] = {
           Mv[0][0], Mv[0][1], Mv[0][2], Mv[0][3],
           Mv[1][0], Mv[1][1], Mv[1][2], Mv[1][3],
           Mv[2][0], Mv[2][1], Mv[2][2], Mv[2][3],
           Mv[3][0], Mv[3][1], Mv[3][2], Mv[3][3]
       };

       float clip[16];
       float t;

       /* Combine the two matrices (multiply projection by modelview) */
       clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
       clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
       clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
       clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

       clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
       clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
       clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
       clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

       clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
       clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
       clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
       clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

       clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
       clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
       clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
       clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

       //Extract the numbers for the right plane
       m_Frustum[0][0] = clip[ 3] - clip[ 0];
       m_Frustum[0][1] = clip[ 7] - clip[ 4];
       m_Frustum[0][2] = clip[11] - clip[ 8];
       m_Frustum[0][3] = clip[15] - clip[12];

       //Normalize the result
       t = sqrt(m_Frustum[0][0] * m_Frustum[0][0] + m_Frustum[0][1] * m_Frustum[0][1] + m_Frustum[0][2] * m_Frustum[0][2] );
       m_Frustum[0][0] /= t;
       m_Frustum[0][1] /= t;
       m_Frustum[0][2] /= t;
       m_Frustum[0][3] /= t;

       //Extract the numbers for the left plane
       m_Frustum[1][0] = clip[ 3] + clip[ 0];
       m_Frustum[1][1] = clip[ 7] + clip[ 4];
       m_Frustum[1][2] = clip[11] + clip[ 8];
       m_Frustum[1][3] = clip[15] + clip[12];

       //Normalize the result
       t = sqrt(m_Frustum[1][0] * m_Frustum[1][0] + m_Frustum[1][1] * m_Frustum[1][1] + m_Frustum[1][2] * m_Frustum[1][2] );
       m_Frustum[1][0] /= t;
       m_Frustum[1][1] /= t;
       m_Frustum[1][2] /= t;
       m_Frustum[1][3] /= t;

       //Extract the bottom plane
       m_Frustum[2][0] = clip[ 3] + clip[ 1];
       m_Frustum[2][1] = clip[ 7] + clip[ 5];
       m_Frustum[2][2] = clip[11] + clip[ 9];
       m_Frustum[2][3] = clip[15] + clip[13];

       //Normalize the result
       t = sqrt(m_Frustum[2][0] * m_Frustum[2][0] + m_Frustum[2][1] * m_Frustum[2][1] + m_Frustum[2][2] * m_Frustum[2][2] );
       m_Frustum[2][0] /= t;
       m_Frustum[2][1] /= t;
       m_Frustum[2][2] /= t;
       m_Frustum[2][3] /= t;

       //Extract the top plane
       m_Frustum[3][0] = clip[ 3] - clip[ 1];
       m_Frustum[3][1] = clip[ 7] - clip[ 5];
       m_Frustum[3][2] = clip[11] - clip[ 9];
       m_Frustum[3][3] = clip[15] - clip[13];

       //Normalize the result
       t = sqrt(m_Frustum[3][0] * m_Frustum[3][0] + m_Frustum[3][1] * m_Frustum[3][1] + m_Frustum[3][2] * m_Frustum[3][2] );
       m_Frustum[3][0] /= t;
       m_Frustum[3][1] /= t;
       m_Frustum[3][2] /= t;
       m_Frustum[3][3] /= t;

       //Extract the far plane
       m_Frustum[4][0] = clip[ 3] - clip[ 2];
       m_Frustum[4][1] = clip[ 7] - clip[ 6];
       m_Frustum[4][2] = clip[11] - clip[10];
       m_Frustum[4][3] = clip[15] - clip[14];

       //Normalize the result
       t = sqrt(m_Frustum[4][0] * m_Frustum[4][0] + m_Frustum[4][1] * m_Frustum[4][1] + m_Frustum[4][2] * m_Frustum[4][2] );
       m_Frustum[4][0] /= t;
       m_Frustum[4][1] /= t;
       m_Frustum[4][2] /= t;
       m_Frustum[4][3] /= t;

       //Extract the near plane
       m_Frustum[5][0] = clip[ 3] + clip[ 2];
       m_Frustum[5][1] = clip[ 7] + clip[ 6];
       m_Frustum[5][2] = clip[11] + clip[10];
       m_Frustum[5][3] = clip[15] + clip[14];

       //Normalize the result
       t = sqrt(m_Frustum[5][0] * m_Frustum[5][0] + m_Frustum[5][1] * m_Frustum[5][1] + m_Frustum[5][2] * m_Frustum[5][2] );
       m_Frustum[5][0] /= t;
       m_Frustum[5][1] /= t;
       m_Frustum[5][2] /= t;
       m_Frustum[5][3] /= t;
}
}
