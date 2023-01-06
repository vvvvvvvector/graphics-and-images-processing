#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glslprogram.h"
#include "geometry.h"
#include "mathgl.h"

const unsigned int window_width = 500;
const unsigned int window_height = 500;

int main(void)
{
    if (!glfwInit())
    {
        std::cout << "GLFW init error.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "OpenGL Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Create window error.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        return -1;
    }

    // -------------geometry def.-------------
    vec2 positions[] = {
        {0.0f, 0.0f},
        {0.5f, 0.0f},
        {0.0f, 0.5f},
        {0.5f, 0.5f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.2f, 0.5f, 1.0f, 1.0f}};

    GLuint indices[] = {0, 1, 2, 3, 2, 1};

    Geometry *figure = new Geometry();

    figure->set_indices(indices, 6);
    figure->set_vertices(0, positions, 4);
    figure->set_vertices(1, colors, 4);
    // -------------geometry def.-------------

    GLSLProgram *basic = new GLSLProgram();

    basic->compile_shaders_from_file("res/shaders/basic.shader");
    basic->link();

    basic->use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        figure->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    basic->delete_program();

    glfwTerminate();

    return 0;
}