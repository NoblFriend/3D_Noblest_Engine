#include <vector>
#include <GL/gl.h>

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
    triangle();
};

struct object {
    vector<vertex> vertices = {}; //лови епта!11
    vector<triangle> triangles = {};
    object(vector<vertex> _vertices, vector<triangle> _triangles):
        vertices (_vertices);
        triangles (_triangles);
    {}
    void draw () {
        glPushMatrix();
            glBegin(GL_TRIANGLES);
                for (int i = 0; i < sizeof(triangles); i++) {
                    for (int v = 0; v < 3; v++)
                        glVertex3d(vertices[triangles[i].vertices[v]].x,vertices[triangles[i].vertices[v]].y,vertices[triangles[i].vertices[v]].z);
                }
            glEnd();
        glPopMatrix();
    }
};

