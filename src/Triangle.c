#include<GL/glew.h>

#include "Triangle.h"
#include "Shader.h"

#include <stdio.h>
#include <stdlib.h>


Triangle* 
create_triangle(Point3D p1 , Point3D p2, Point3D p3)
{
    Triangle* tri = malloc(sizeof(Triangle));

    if (tri == NULL ) {
        printf("failed to create triangle\n");
        return NULL;
    }

    tri->p1 = p1;
    tri->p2 = p2;
    tri->p3 = p3;

    return tri;
}

static unsigned int 
compile_shader(const char* shader_src, unsigned int type)
{
    unsigned int shade = glCreateShader(type);
    glShaderSource(shade,1,&shader_src,NULL);
    glCompileShader(shade);

    printf("done compiling shader\n");

    return shade;
}

static void 
set_shader(Triangle* tri,const char *vertex_shader_file_name,const char* fragmennt_shader_file_name)
{

    const char* vertex_shader_src     = read_shader(vertex_shader_file_name);
    const char* fragmennt_shader_src  = read_shader(fragmennt_shader_file_name);

    unsigned int shader_program     = glCreateProgram();
    unsigned int vertex_shader      = compile_shader(vertex_shader_src,GL_VERTEX_SHADER); 
    unsigned int fragment_shader    = compile_shader(fragmennt_shader_src,GL_FRAGMENT_SHADER); 

    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    printf("done creating shader\n");
    
    tri->PROGRAM = shader_program;
}


static void 
set_buffers(Triangle* tri)
{
    if (tri == NULL) {printf("triangle is null\n");return;}

    float vertices[] = {
        tri->p1.x , tri->p1.y , tri->p1.z,  1.0f, 0.0f,0.0f,
        tri->p2.x , tri->p2.y , tri->p2.z,  0.0f, 1.0f,0.0f,
        tri->p3.x , tri->p3.y , tri->p3.z,  0.0f, 0.0f,1.0f
    };

    unsigned int VBO,VAO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); 

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    tri->VAO = VAO;
    tri->VBO = VBO;
}

void 
init_triangle(Triangle* t,const char *vertex_shader_src,const char* fragmennt_shader_src)
{
    set_shader(t,vertex_shader_src,fragmennt_shader_src);
    set_buffers(t);
}


void 
draw_trianlges(Triangle* t)
{
    glUseProgram(t->PROGRAM);

    glBindVertexArray(t->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void 
destroy_triangle(Triangle* t)
{
    glDeleteVertexArrays(1,&t->VAO);
    glDeleteBuffers(1,&t->VBO);
    glDeleteProgram(t->PROGRAM);

    free(t);
    t = NULL;
    printf("cleared triangle\n");
}