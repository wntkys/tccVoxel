#include "OS_Dep.h"
#include "Camera_Works.h"

void init()
{
    camera.x = 0;
    camera.y = 0;
    camera.maxSpeedX = 2;
    camera.maxSpeedY = 1;

}

void render()
{
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glEnd();
    translateByCamera();
    const int vert[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_INT, 0, &vert);
    for (int i = -10; i <= 10; i++)
    {
        for (int j = -10; j <= 10; j++)
        {
            glPushMatrix();
            if ((i + j) % 2 == 0) glColor3ub(34,139,34);
            else glColor3ub(0,207,0);
            glTranslatef(i*2, j*2, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void update(DWORD delta)
{
    MoveCamera(delta);
}

int main()
{
    initRL(*init,*render, *update);
}
