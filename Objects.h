#pragma once
#include <vector>
#include <cmath>
#include "glut.h"

struct basematerial 
{
    int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
    char HEX_color[8];

    basematerial ( char color[8] );

    basematerial ();
};

struct materials 
{
    std::vector<basematerial> basematerials;
    //std::vector<texture> textures;

    materials ( std::vector<basematerial> _basematerials );

    materials();
};

struct vertex 
{
    double x = 0;
	double y = 0;
	double z = 0;

    vertex ( double _x, double _y, double _z );

    vertex();
};

struct triangle 
{
    int vertices[3] = { 0, 0, 0};
    int material = 0;

    triangle ( int first, int second, int third, int _material );

    triangle ( int first, int second, int third );
};

struct object 
{
	std::vector<vertex>		vertices  = {};
	std::vector<triangle>	triangles = {};

    object ( std::vector<vertex> _vertices, std::vector<triangle> _triangles );

    void draw ();
};