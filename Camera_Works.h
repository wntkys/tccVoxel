#ifndef CAMERA_WORKS_H_INCLUDED
#define CAMERA_WORKS_H_INCLUDED
#include "myMath.h"
#include "math.h"

struct Camera{
    float xAlfa;
    float yAlfa;
    float x;
    float y;
    float speedX;
    float speedY;
    float maxSpeedX;
    float maxSpeedY;
    float speed;
};

struct Camera camera;

void MoveCamera(DWORD delta)
{
    if (GetKeyState(VK_UP) < 0)
    {
        camera.speedX+= 0.2;
        if (camera.speedX > camera.maxSpeedX) camera.speedX = camera.maxSpeedX;
    }
    if (GetKeyState(VK_DOWN) < 0)
    {
        camera.speedX-= 0.2;
        if (camera.speedX < -camera.maxSpeedX) camera.speedX = -camera.maxSpeedX;
    }
    if (GetKeyState(VK_DOWN) >= 0 && GetKeyState(VK_UP) >= 0)
    {
        camera.speedX *= 0.4;
    }

    camera.xAlfa = camera.xAlfa + camera.speedX;
    if (camera.xAlfa> 180)
    {
        camera.xAlfa = 180;
        camera.speedX = 0;
    }
    if (camera.xAlfa< -180)
    {
        camera.xAlfa = -180;
        camera.speedX = 0;
    }

    if (GetKeyState(VK_RIGHT) >= 0 && GetKeyState(VK_LEFT) >= 0)
    {
        camera.speedY *= 0.4;
    }
    if (GetKeyState(VK_LEFT) < 0)
    {
        camera.speedY+= 0.2;
        if (camera.speedY > camera.maxSpeedY) camera.speedY = camera.maxSpeedY;
    }
    if (GetKeyState(VK_RIGHT) < 0)
    {
        camera.speedY-= 0.2;
        if (camera.speedY < -camera.maxSpeedY) camera.speedY = -camera.maxSpeedY;
    }

    camera.yAlfa = camera.yAlfa + camera.speedY;

    float ugol = -camera.yAlfa /180 * M_PI;
    float deltaUgol = 0;
    camera.speed = 0; //super duper movement technology
    float count = 0;
    float lrsp = 0;
    float fdsp = 0;

    if (GetKeyState('W') < 0)
    {
        fdsp += +0.02 * delta;
    }
    if (GetKeyState('S') < 0)
    {
        fdsp -= 0.02 * delta;
    }
    if (GetKeyState('A') < 0)
    {
        lrsp -= 0.02 * delta;
    }
    if (GetKeyState('D') < 0)
    {
        lrsp += 0.02 * delta;
    }

    //float speed = 0;
    if (lrsp != 0 || fdsp != 0)
    {
        if (lrsp != 0 && fdsp != 0)
        {
            camera.x += sin(ugol) * fdsp * SQ_R;
            camera.y += cos(ugol) * fdsp * SQ_R;
            camera.x += sin(ugol + M_PI / 2) * lrsp * SQ_R;
            camera.y += cos(ugol + M_PI / 2) * lrsp * SQ_R;
        }
        else if (lrsp != 0)
        {
            camera.x += sin(ugol + M_PI / 2) * lrsp;
            camera.y += cos(ugol + M_PI / 2) * lrsp;
        }
        else
        {
            camera.x += sin(ugol) * fdsp;
            camera.y += cos(ugol) * fdsp;
        }
    }
}

void translateByCamera()
{
    glRotatef(-camera.xAlfa, 1, 0, 0);
    glRotatef(-camera.yAlfa, 0, 0, 1);
    glTranslatef(-camera.x,-camera.y, -3);
}

void updateCamera()
{

}

#endif // CAMERA_WORKS_H_INCLUDED
