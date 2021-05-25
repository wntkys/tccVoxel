#include "OS_Dep.h"
#include "Camera_Works.h"
#include "Voxel_Works.h"
#include "math.h"
#include "Entity.h"
#include "effex.h"
#include "AICE.h"

struct voxelMesh vm;

struct entity* zayac;


void init()
{
    camera.x = 0;
    camera.y = 0;
    camera.maxSpeedX = 2;
    camera.maxSpeedY = 1;
    camera.xAlfa = 90;
    genCube(&vm);
    zayac = initAICE();
    calcCulling(&vm);
}

void render()
{

    translateByCamera();
    drawVM(&vm);
    /*glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2f(-10,-10);
    glVertex2f(10,-10);
    glVertex2f(10,10);
    glVertex2f(-10,10);
    glEnd();*/
    drawZayac(zayac);
}

void update(DWORD delta)
{
    MoveCamera(delta);
    updateZayac(zayac, delta);
    //printf("%i ", delta);
}

int main()
{
    initRL(*init,*render, *update);
}
