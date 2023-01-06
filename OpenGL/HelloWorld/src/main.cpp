#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glslprogram.h"
#include "mathgl.h"
#include "primitives.h"

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

    // Geometry *geometry = createAxes();
    // Geometry *geometry = createTriangle();
    Geometry *geometry = createSquare();

    GLSLProgram *base = new GLSLProgram();
    base->compile_shaders_from_file("res/shaders/base.shader");
    base->link();
    base->use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        geometry->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    base->delete_program();

    glfwTerminate();

    return 0;
}