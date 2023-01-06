#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    // Geometry *axes = createAxes();
    // Geometry *triangle = createTriangle();
    Geometry *square = createSquare();

    GLSLProgram *base = new GLSLProgram();
    base->compile_shaders_from_file("res/shaders/base.shader");
    base->link();
    base->use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // axes->render();
        square->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}