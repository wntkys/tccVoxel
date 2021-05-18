#ifndef OS_DEP_H_INCLUDED
#define OS_DEP_H_INCLUDED
#include <windows.h>
#include <gl/gl.h>
//#include <GL/wglext.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void ResizeWindow();


struct RigelWindowData
{
    float aspectRatio;
    DWORD sizeX, sizeY;
    char fullscreen;
    DWORD maxSizeX, maxSizeY;
    DWORD cursorPosX, cursorPosY;
    float cursorPosXf, cursorPosYf;
};

struct RigelWindowData RWD;

int initRL(void (*renderFunc)(), void(*updateFunc)())
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(0);
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RWD.maxSizeX  = GetSystemMetrics(SM_CXSCREEN);
    RWD.maxSizeY = GetSystemMetrics(SM_CYSCREEN);

    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          512,
                          512,
                          NULL,
                          NULL,
                          wcex.hInstance,
                          NULL);
    RWD.sizeX = 512;
    RWD.sizeY = 512;
    RWD.aspectRatio = 1;
    ShowWindow(hwnd, SW_NORMAL);
    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);
    DWORD currentTime = GetTickCount();
    DWORD oldTime = GetTickCount();
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        renderFunc();
        glPopMatrix();
        SwapBuffers(hDC);
        POINT p;
        if (GetCursorPos(&p))
        {
            ScreenToClient(hwnd, &p);
            RWD.cursorPosX = p.x;
            RWD.cursorPosY = p.y;
            RWD.cursorPosXf = (((float)p.x/RWD.sizeX)*2 -1)*RWD.aspectRatio;
            RWD.cursorPosYf = (((float)p.y/RWD.sizeY)*-2 + 1);
            //printf("%i\n",RWD.sizeX);
        }
        updateFunc();
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYUP:
        switch (wParam)
        {
        case '1':
            if (RWD.fullscreen == 0)
            {
                SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
                SetWindowPos(hwnd, HWND_TOP, 0,0, RWD.maxSizeX,RWD.maxSizeY, SWP_SHOWWINDOW);
                RWD.fullscreen = 1;
            }
            else
            {
                SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                SetWindowPos(hwnd, HWND_TOP, 0,0, 640,480, SWP_SHOWWINDOW);
                RWD.fullscreen = 0;
            }
            break;
        }
        break;
    case WM_SIZE:
        RWD.sizeX = LOWORD(lParam);
        RWD.sizeY = HIWORD(lParam);
        ResizeWindow();
        break;

    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }
    break;

    case WM_CREATE:
        RWD.sizeX = ((CREATESTRUCT*)lParam)->cx;
        RWD.sizeY = ((CREATESTRUCT*)lParam)->cy;
        ResizeWindow();
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
    //PFNWGLSWAPINTERVALEXTPROC pfnwglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    //if(pfnwglSwapIntervalEXT != NULL)
    //pfnwglSwapIntervalEXT(1);// or 0 to disable vsync, test and see which looks best
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void ResizeWindow()
{
    RWD.aspectRatio = RWD.sizeX / (float)RWD.sizeY;
    glLoadIdentity();
    glViewport(0, 0, RWD.sizeX, RWD.sizeY);
    glOrtho(-RWD.aspectRatio,RWD.aspectRatio, -1,1, 0, 2);
    //glFrustum(-k,k, -1,1, 0,2);
}


#endif // OS_DEP_H_INCLUDED
