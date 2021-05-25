#ifndef VOXEL_WORKS_H_INCLUDED
#define VOXEL_WORKS_H_INCLUDED
#include <GL/gl.h>

#define chunkSizes 16
#define transparentMaterialsCount 128

struct voxelMesh
{
    short data[chunkSizes][chunkSizes][chunkSizes];
    unsigned char culling[chunkSizes][chunkSizes][chunkSizes];
};

void genCube(struct voxelMesh* v)
{
    for(char i = 0; i < chunkSizes; i++)
    {
        for(char j = 0; j < chunkSizes; j++)
        {
            for(char k = 0; k < chunkSizes; k++)
            {
                v->data[i][j][k] = 10 + i*j*k;
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
                //printf("%i ",v->data[i][j][k]);
                v->culling[i][j][k] = 0b11111111;
                if(v->data[i][j][k] <= transparentMaterialsCount)
                {
                    v->culling[i][j][k] = 0b00000000;
                    continue;
                }
                if(i!=0)
                {
                    if(v->data[i-1][j][k] > transparentMaterialsCount) {v->culling[i][j][k] &= 0b01111111;}
                }
                if(i!=chunkSizes-1)
                {
                    if(v->data[i+1][j][k] > transparentMaterialsCount) {v->culling[i][j][k] &= 0b10111111;}
                }
                if(j!=0)
                {
                    if(v->data[i][j-1][k] > transparentMaterialsCount) {v->culling[i][j][k] &= 0b11011111;}
                }
                if(j!=chunkSizes-1)
                {
                    if(v->data[i][j+1][k] > transparentMaterialsCount) {v->culling[i][j][k] &= 0b11101111;}
                }
                if(k!=0)
                {
                    if(v->data[i][j][k-1] > transparentMaterialsCount) {v->culling[i][j][k] &= 0b11110111;}
                }
                if(k!=chunkSizes-1)
                {
                    if(v->data[i][j][k+1] > transparentMaterialsCount) {v->culling[i][j][k] &= 0b11111011;}
                }
            //printf("%i ",v->culling[i][j][k]);
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
                glLineWidth(2);

                glColor3f((float)i/16,(float)j/16,(float)k/16);
                glBegin(GL_QUADS);
                if((v->culling[i][j][k] & 0b10000000) != 0) // leftSide
                {
                    glVertex3i(-1,1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,-1,1);
                    glVertex3i(-1,1,1);
                }
                if((v->culling[i][j][k] & 0b01000000) != 0) //rigtSide
                {
                    glVertex3i(1,1,-1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(1,-1,1);
                    glVertex3i(1,1,1);
                }

                if((v->culling[i][j][k] & 0b00100000) != 0) //upperSide
                {
                    glVertex3i(1,-1,1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,-1,1);
                }
                if((v->culling[i][j][k] & 0b00010000) != 0) //downerSide
                {

                    glVertex3i(1,1,1);
                    glVertex3i(1,1,-1);
                    glVertex3i(-1,1,-1);
                    glVertex3i(-1,1,1);
                }
                if((v->culling[i][j][k] & 0b00001000) != 0) //nearerSide
                {
                    glColor3f((float)i/18,(float)j/18,(float)k/18);

                    glVertex3i(1,1,-1);
                    glVertex3i(1,-1,-1);
                    glVertex3i(-1,-1,-1);
                    glVertex3i(-1,1,-1);
                }
                if((v->culling[i][j][k] & 0b00000100) != 0) //farerSide
                {
                    glColor3f((float)i/14,(float)j/14,(float)k/14);
                    glVertex3i(1,1,1);
                    glVertex3i(1,-1,1);
                    glVertex3i(-1,-1,1);
                    glVertex3i(-1,1,1);

                }
                glEnd();
                glPopMatrix();
            }
        }
    }
}

struct chunkMesh
{

};

//
//
//      /\
//      ||
//  <-     ->
//      ||
//      \/
//
#endif // VOXEL_WORKS_H_INCLUDED
