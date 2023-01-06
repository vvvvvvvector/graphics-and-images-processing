#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glslprogram.h"

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

    float positions[] = {
        0.0f, 0.0f,
        0.5f, 0.0f,
        0.0f, 0.5f,
        0.5f, 0.5f};

    float colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.2f, 0.5f, 1.0f, 1.0f};

    GLuint indices[] = {0, 1, 2, 3, 2, 1};

    GLuint vbo, cbo, ibo; // id for my buffers

    GLuint vao;

    // -------------geometry def.-------------
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // -------------vbo-------------
    glGenBuffers(1, &vbo);                                                         // generating id for my buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                            // selecting my buffer; work on this buffer
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);   // this buffer contains vertex positions
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0); // specifying layout of data here (each vertex is 2 floats, which in this array, are at a distance of 2 * sizeof(float) from each other)
    glEnableVertexAttribArray(0);                                                  // fire this attribute(position, texture, ...)
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                              // unselect my buffer
    // -------------vbo-------------

    // -------------ibo-------------
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    // -------------ibo-------------

    // -------------cbo-------------
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // -------------cbo-------------

    glBindVertexArray(0);
    // -------------geometry def.-------------

    GLSLProgram *shader = new GLSLProgram();

    shader->compile_shaders_from_file("res/shaders/basic.shader");
    shader->link();

    shader->use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);                                      // its like glBegin?
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0); // draw call -> should draw a triangle
        glBindVertexArray(0);                                        // its like glEnd?

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    shader->delete_program();

    glfwTerminate();

    return 0;
}