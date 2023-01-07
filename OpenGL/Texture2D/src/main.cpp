#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
#include "texture2d.h"
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

    vec2 texture_coordinates[] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}};

    square->set_attribute(7, texture_coordinates, 4);

    int grass_tex_unit = 4;
    Texture2D *texture = new Texture2D();
    texture->load_texture_from_file("res/textures/metal.jpg");
    texture->bind(grass_tex_unit);

    GLSLProgram *texture_shader = new GLSLProgram();
    texture_shader->set_uniform("SamplerTex", grass_tex_unit);
    texture_shader->compile_shaders_from_file("res/shaders/texture.shader");
    texture_shader->link();
    texture_shader->use();

    // GLSLProgram *base = new GLSLProgram();
    // base->compile_shaders_from_file("res/shaders/base.shader");
    // base->link();
    // base->use();

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