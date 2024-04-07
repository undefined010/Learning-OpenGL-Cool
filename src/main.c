#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "Triangle.h"
#include "Shader.h"

/* window values */
static  const unsigned  WINDOW_WIDTH  = 800;
static  const unsigned  WINDOW_HEIGHT = 600;



void 
process_window_input (GLFWwindow* window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window,true);
}

int 
main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = NULL;

    window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Ahmad Craft",NULL,NULL);

    if (window == NULL) {
        printf("failed to create a glfw window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        printf("glew failed\n");
        return -2;
    }


    Triangle* tri = create_triangle((Point3D){-0.5,-0.5,0.0},(Point3D){0.5,-0.5,0.0},(Point3D){0.0,0.5,0.0});
    

    init_triangle(tri ,"GLSL/vertex_shader.vs" ,"GLSL/fragment_shader2.fs");
    

    while (!glfwWindowShouldClose(window))
    {

        process_window_input(window);

        glClearColor(0.1,0.2,0.3,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        draw_trianlges(tri);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroy_triangle(tri);
    
    glfwTerminate();
    

    return 0;

}