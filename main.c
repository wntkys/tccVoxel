#include "OS_Dep.h"


void render()
{
    glTranslatef(RWD.cursorPosXf, RWD.cursorPosYf, 0);
    //glTranslatef(-RWD.aspectRatio,1,0);
    //printf("%f %f\n",RWD.cursorPosYf, RWD.cursorPosXf);
    glScalef(0.1,0.1, 1);

    glBegin(GL_QUADS);
    glColor3f(1,0.5, 0.2);
    glVertex2f(-1,1);
    glVertex2f(-1,-1);
    glColor3f(0.2,1, 0.2);
    glVertex2f(1,-1);
    glVertex2f(1,1);
    glEnd();
}

void update()
{
    //printf("pishov nahui\n");
}

int main()
{
    initRL(*render, *update);
}
