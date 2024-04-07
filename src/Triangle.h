#ifndef  TRIANGLE_H__
#define TRIANGLE_H__

#include "Point.h"

typedef struct Triangle_t
{
    Point3D p1,p2,p3; // triangle has 3 heads
    unsigned int VBO,VAO,PROGRAM;
} Triangle;

typedef struct Shader_t
{
    char* vertex_shader;
    char* fragment_shader;
} Shader;



Triangle* create_triangle(Point3D p1 , Point3D p2 , Point3D p3);
void destroy_triangle(Triangle* t);

void init_triangle(Triangle* t,const char *vertex_shader_src,const char* fragmennt_shader_src);

void draw_trianlges(Triangle* t);

#endif