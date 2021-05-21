#ifndef VOXEL_WORKS_H_INCLUDED
#define VOXEL_WORKS_H_INCLUDED
#include <GL/gl.h>

#define chunkSizes 16

struct voxelMesh
{
    short[chunkSizes][chunkSizes][chunkSizes] data;
    char[chunkSizes][chunkSizes][chunkSizes] culling;
};

void calcCulling(struct voxelMesh* v)
{
    for(char i = 0; i < chunkSizes; i++)
    {
        for(char j = 0; j < chunkSizes; j++)
        {
            for(char k = 0; k < chunkSizes; k++)
            {
                v->culling = 255;
            }
        }
    }
}

void drawVM(struct voxelMesh* v)
{
    for(char i = 0; i < chunkSizes; i++)
    {
        for(char j = 0; j < chunkSizes; j++)
        {
            for(char k = 0; k < chunkSizes; k++)
            {
                glBegin(GL_QUADS)
                glPushMatrix();
                glTranslatef(i*2 - chunkSizes + 1, j*2 - chunkSizes + 1, z*2 - chunkSizes + 1)
                glColor3f(float(i)/16,float(j)/16,float(k)/16);
                if(v->culling & 10000000b) // leftSide
                {
                    glVertex3i(-1,1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,-1,1);
                    glVertex3i(-1,1,1);
                }
                if(v->culling & 01000000b) //rigtSide
                {
                    glVertex3i(1,1,-1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(1,-1,1);
                    glVertex3i(1,1,1);
                }
                if(v->culling & 00100000b) //upperSide
                {
                    glVertex3i(1,1,1);
                    glVertex3i(1,-1,1);
                    glVertex3i(-1,-1,1);
                    glVertex3i(-1,1,1);
                }
                if(v->culling & 00010000b) //upperSide
                {
                    glVertex3i(1,1,-1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,1,-1);
                }
                if(v->culling & 00001000b) //nearerSide
                {
                    glVertex3i(1,1,1);
                    glVertex3i(1,1,-1);
                    glVertex3i(-1,1,-1);
                    glVertex3i(-1,1,1);
                }
                if(v->culling & 00000100b) //farerSide
                {
                    glVertex3i(1,-1,1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,-1,1);
                }
                glPopMatrix();
                glEnd();
            }
        }
    }
}

//
//
//      /\
//      ||
//  <-     ->
//      ||
//      \/
//
#endif // VOXEL_WORKS_H_INCLUDED
