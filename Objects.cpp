#include "Objects.h"


    basematerial::basematerial ( char color[8] ) 
	{
        for ( int i = 0; i<8; i++ ) 
		{
            HEX_color[i] = color[i];
            switch (i) 
			{
                case 1:
					r+=color[i];
					break;
                case 2: 
					r+=color[i];
					break;
                case 3:
					g+=color[i];
					break;
                case 4:
					g+=color[i];
					break;
                case 5: 
					b+=color[i];break;
                case 6: b+=color[i];
					break;
                case 7:
					a+=color[i];
					break;
                case 8: 
					a+=color[i];
					break;
            }
        }
    }

    basematerial::basematerial () {}



    materials::materials ( std::vector<basematerial> _basematerials )
	{
        basematerials = _basematerials;
    }

	materials::materials() {}



    vertex::vertex ( double _x, double _y, double _z )
    {
        x = _x;
        y = _y;
        z = _z;
    }

    vertex::vertex() {}



    triangle::triangle ( int first, int second, int third, int _material ) 
	{
        vertices[0] = first;
        vertices[1] = second;
        vertices[2] = third;
        material	= _material;
    }

    triangle::triangle ( int first, int second, int third ) 
	{
        vertices[0] = first;
        vertices[1] = second;
        vertices[2] = third;
    }



    object::object ( std::vector<vertex> _vertices, std::vector<triangle> _triangles ) 
	{
        for ( int i = 0; i < _vertices.size(); i++ ) 
		{
            vertices.push_back ( _vertices[i] ); 
        }

        for ( int i = 0; i < _triangles.size(); i++ )
		{
            triangles.push_back ( _triangles[i] );
        }
    }

    void object::draw () 
	{
        glPushMatrix ();
            glBegin ( GL_TRIANGLES );

                for (int i = 0; i < triangles.size (); i++ ) 
				{
                    for (int v = 0; v < 3; v++)
					{
                        glVertex3d ( vertices[triangles[i].vertices[v]].x,
									 vertices[triangles[i].vertices[v]].y,
									 vertices[triangles[i].vertices[v]].z );
					}
                }

            glEnd();
        glPopMatrix();
    }
