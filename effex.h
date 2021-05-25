#ifndef EFFEX_H_INCLUDED
#define EFFEX_H_INCLUDED
#include "Entity.h"
#include "math.h"
#include "myMath.h"


struct effex //over entity
{
    DWORD time;
    DWORD seed;
};

void drawEff(struct entity* e)
{
    struct effex* eff = (struct effex*)(e->heap);
    glPushMatrix();
    glLineWidth(4);
    for(int i = 0; i < 10; i++)
    {
        glTranslatef(0,0,-sin(((float)eff->time)/1000 + eff->seed) + -sin(((float)eff->time)/300 + eff->seed) + 2);
        glScalef(0.9,0.9,0.9);
        glBegin(GL_LINE_LOOP);

        glColor3f((1 + sin(i * 2))/2, (1 + sin(i*3))/2, (1 + sin(i * 0.6)) / 2);
        glVertex3i(-10,-10,0);
        glVertex3i(10,-10,0);
        glVertex3i(10,10,0);
        glVertex3i(-10,10,0);
        glEnd();
    }

    glPopMatrix();
}

void updateEff(struct entity* e, DWORD delta)
{
    struct effex* eff = (struct effex*)(e->heap);
    eff->time += delta;
}

void initEffex(struct entity* e)
{
    e->heap = malloc(sizeof(struct effex));
}

#endif // ENTITY_H_INCLUDED
