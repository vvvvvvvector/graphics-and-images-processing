#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
#include "texture2d.h"
#include "mathgl.h"

int init_glfw();
int init_glad();
GLFWwindow *glfw_create_window(int, int, const char *);

const unsigned int window_width = 500;
const unsigned int window_height = 500;

int main(void)
{
    //----------------init----------------
    init_glfw();

    GLFWwindow *window = glfw_create_window(window_width, window_height, "Textures2D");

    glfwMakeContextCurrent(window);

    init_glad();
    //----------------init----------------

    Geometry *square = create_square();

    vec2 texture_coordinates[] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f}};

    square->set_attribute(7, texture_coordinates, 4);

    GLSLProgram *shader = new GLSLProgram();
    shader->compile_shaders_from_file("res/shaders/mix_textures.shader");
    shader->link();
    shader->use();

    unsigned int wood_tex_slot = 10;
    Texture2D *wood = new Texture2D("res/textures/wood.jpg", wood_tex_slot);
    wood->bind(wood_tex_slot);
    shader->set_uniform("texture_1", wood_tex_slot);

    unsigned int metal_tex_slot = 15;
    Texture2D *metal = new Texture2D("res/textures/metal.jpg", metal_tex_slot);
    metal->bind(metal_tex_slot);
    shader->set_uniform("texture_2", metal_tex_slot);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        square->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

int init_glfw()
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

    return 0;
}

int init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        return -1;
    }

    return 0;
}

GLFWwindow *glfw_create_window(int width, int height, const char *name)
{
    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
    {
        std::cout << "Create window error.\n";
        glfwTerminate();
        return nullptr;
    }

    return window;
}