#include <Windows.h>
#include "glut.h"
#include <vector>

struct basematerial {
    int r=0,g=0,b=0,a=0;
    char HEX_color[8];
    basematerial(char color[8]) {
        for (int i = 0; i<8; i++) {
            HEX_color[i] = color[i];
            switch (i) {
                case 1: r+=color[i];break;
                case 2: r+=color[i];break;
                case 3: g+=color[i];break;
                case 4: g+=color[i];break;
                case 5: b+=color[i];break;
                case 6: b+=color[i];break;
                case 7: a+=color[i];break;
                case 8: a+=color[i];break;
            }
        }
    }
    basematerial() {}
};

struct materials {
    std::vector<basematerial> basematerials;
    /* std::vector<texture> textures; */
    materials( std::vector<basematerial> _basematerials ) {
        basematerials = _basematerials;
    }
    materials() {}
};

struct vertex {
    double x,y,z;
    vertex(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    vertex() {}
};

struct triangle {
    int vertices[3] {0,0,0};
    int material = 0;
    triangle(int first, int second, int third, int _material) {
        vertices[0] = first;
        vertices[1] = second;
        vertices[2] = third;
        material = _material;
    }
    triangle(int first, int second, int third) {
        vertices[0] = first;
        vertices[1] = second;
        vertices[2] = third;
    }
};

struct object {
	std::vector<vertex> vertices = {};
	std::vector<triangle> triangles = {};
    object(std::vector<vertex> _vertices, std::vector<triangle> _triangles) {
        for (int i = 0; i < _vertices.size(); i++) {
            vertices.push_back (_vertices[i]); 
        }
        for (int i = 0; i < _triangles.size(); i++) {
            triangles.push_back(_triangles[i]);
        }
    }
    void draw () {
        glPushMatrix();
            glBegin(GL_TRIANGLES);
                for (int i = 0; i < triangles.size(); i++) {
                    for (int v = 0; v < 3; v++)
                        glVertex3d(vertices[triangles[i].vertices[v]].x,vertices[triangles[i].vertices[v]].y,vertices[triangles[i].vertices[v]].z);
                }
            glEnd();
        glPopMatrix();
    }
};

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };

    int iFormat;

    *hDC = GetDC(hwnd);


    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC){
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    switch (Msg) {
        case WM_CLOSE: PostQuitMessage(0);break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
            switch (wParam) {
                case VK_ESCAPE:PostQuitMessage(0);break;
            }break;

        default:
            return DefWindowProc(hwnd, Msg, wParam, lParam);
    }

    return 0;
}

WNDCLASSEX GLSample () {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0,128,128));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

    return wc;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = GLSample();
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    std::vector<vertex> vertices = {vertex(0,0,0),vertex(1,0,0),vertex(0,1,0),vertex(0,0,1)};
    std::vector<triangle> triangles = {triangle(0,1,2),triangle(0,1,3),triangle(0,2,3),triangle(1,2,3)};
    object obj = object(vertices,triangles);

    double phi = 0;

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
