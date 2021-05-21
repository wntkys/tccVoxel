#ifndef VOXEL_WORKS_H_INCLUDED
#define VOXEL_WORKS_H_INCLUDED
#include <GL/gl.h>

#define chunkSizes 16


struct voxelMesh
{
    short data[chunkSizes][chunkSizes][chunkSizes];
    char culling[chunkSizes][chunkSizes][chunkSizes];
};

void genCube(struct voxelMesh* v)
{
    for(char i = 0; i < chunkSizes; i++)
    {
        for(char j = 0; j < chunkSizes; j++)
        {
            for(char k = 0; k < chunkSizes; k++)
            {
                v->data[i][j][k] = 255;
            }
        }
    }
}

void calcCulling(struct voxelMesh* v)
{
    for(char i = 0; i < chunkSizes; i++)
    {
        for(char j = 0; j < chunkSizes; j++)
        {
            for(char k = 0; k < chunkSizes; k++)
            {
                if(i==0 || i==chunkSizes-1 || j==0 || j==chunkSizes-1 || k==0 || k==chunkSizes-1)
                    v->culling[i][j][k] = 255;
                else
                    v->culling[i][j][k] = 0;
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
                glPushMatrix();
                glTranslatef(i*2, j*2, k*2);
                glBegin(GL_QUADS);

                glColor3f((float)i/16,(float)j/16,(float)k/16);
                if(v->culling[i][j][k] & 0b10000000 != 0) // leftSide
                {
                    glVertex3i(-1,1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,-1,1);
                    glVertex3i(-1,1,1);
                }
                if(v->culling[i][j][k] & 0b01000000 != 0) //rigtSide
                {
                    glVertex3i(1,1,-1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(1,-1,1);
                    glVertex3i(1,1,1);
                }
                if(v->culling[i][j][k] & 0b00100000 != 0) //upperSide
                {
                    glVertex3i(1,1,1);
                    glVertex3i(1,-1,1);
                    glVertex3i(-1,-1,1);
                    glVertex3i(-1,1,1);
                }
                if(v->culling[i][j][k] & 0b00010000 != 0) //upperSide
                {
                    glVertex3i(1,1,-1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,1,-1);
                }
                if(v->culling[i][j][k] & 0b00001000 != 0) //nearerSide
                {
                    glVertex3i(1,1,1);
                    glVertex3i(1,1,-1);
                    glVertex3i(-1,1,-1);
                    glVertex3i(-1,1,1);
                }
                if(v->culling[i][j][k] & 0b00000100 != 0) //farerSide
                {
                    glVertex3i(1,-1,1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,-1,1);
                }

                glEnd();
                glPopMatrix();
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
