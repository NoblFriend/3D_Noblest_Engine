#include <gl/gl.h>
#include <windows.h>
#include "myownglut.cpp"      //    ^^
#include "myownwindowslib.cpp"//    :3
#include "object.cpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = GLSample();
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    vertex vertices[4] = {vertex(0,0,0),vertex(1,0,0),vertex(0,1,0),vertex(0,0,1)};
    triangle triangles[4] = {triangle(0,1,2),triangle(0,1,3),triangle(0,2,3),triangle(1,2,3)};
    object obj = object(vertices,triangles);

    double phi;

    if (!RegisterClassEx(&wc))
        return 1;

    hwnd = CreateWindowEx(0,"GLSample","OpenGL Sample",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,256,256,NULL,NULL,NULL,NULL);

    ShowWindow(hwnd, nCmdShow);

    EnableOpenGL(hwnd, &hDC, &hRC);

    while (!bQuit) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            obj.draw();

            glPushMatrix();
            glRotatef(phi, 0.0f, 0.0f, 1.0f);

            glBegin(GL_TRIANGLES);

                glColor3f(phi/255, 1-phi/255, 0.0f);   glVertex2f(0.0f,   1.0f);
                glColor3f(0.0f, phi/255, 1-phi/255);   glVertex2f(0.87f,  -0.5f);
                glColor3f(1-phi/255, 0.0f, phi/255);   glVertex2f(-0.87f, -0.5f);

            glEnd();

            glPopMatrix();

            SwapBuffers(hDC);
            phi++;
            Sleep (10);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);

    DestroyWindow(hwnd);

    return msg.wParam;
}
