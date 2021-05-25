#ifndef AICE_H_INCLUDED
#define AICE_H_INCLUDED
#include "math.h";
//
// Artificial Inteligence Controlled Entities
//
struct aICE //based on entity struct
{
    unsigned char phase;
    DWORD time;
};

struct entity* initAICE()
{
    struct entity* e;
    e = malloc(sizeof(struct entity));
    e->heap = malloc(sizeof(struct aICE));
    return e;
}


void drawZayac(struct entity* e)
{
    glPushMatrix();
    glTranslatef(e->x,e->y,e->z);
    glRotatef(e->xAlfa,1,0,0);
    glRotatef(e->yAlfa,0,1,0);
    glRotatef(e->zAlfa,0,0,1);
    glBegin(GL_QUADS);
    glColor3ub(255,236,173);
    glVertex3f(-0.8,0.8,0);
    glVertex3f(-0.8,-0.8,0);
    glVertex3f(-0.8,-0.8,2);
    glVertex3f(-0.8,0.8,2);
    glVertex3f(0.8,0.8,0);
    glVertex3f(0.8,-0.8,0);
    glVertex3f(0.8,-0.8,2);
    glVertex3f(0.8,0.8,2);

    glColor3ub(235,216,153);
    glVertex3f(0.8,-0.8,0);
    glVertex3f(-0.8,-0.8,0);
    glVertex3f(-0.8,-0.8,2);
    glVertex3f(0.8,-0.8,2);
    glVertex3f(0.8,0.8,0);
    glVertex3f(-0.8,0.8,0);
    glVertex3f(-0.8,0.8,2);
    glVertex3f(0.8,0.8,2);

    glColor3ub(215,196,133);
    glVertex3f(0.8,-0.8,0);
    glVertex3f(-0.8,-0.8,0);
    glVertex3f(-0.8,0.8,0);
    glVertex3f(0.8,0.8,0);

    glColor3ub(255,255,215);
    glVertex3f(0.8,-0.8,2);
    glVertex3f(-0.8,-0.8,2);
    glVertex3f(-0.8,0.8,2);
    glVertex3f(0.8,0.8,2);

    glEnd();
    glPopMatrix();
}

void updateZayac(struct entity* e, DWORD delta)
{
    //printf("cock");
    ((struct aICE*)(e->heap))->time += delta;
    //printf("cock");
    e->x = sin(((float)(((struct aICE*)(e->heap))->time)) / 100);
    e->y = cos(((float)(((struct aICE*)(e->heap))->time)) / 100);

}




#endif // AICE_H_INCLUDED
