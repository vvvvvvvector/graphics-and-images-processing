#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
#include "texture2d.h"
#include "mathgl.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

int init_glfw();
int init_glad();
GLFWwindow *init_window(int, int, const char *);

int main(void)
{
    //----------------init----------------
    init_glfw();

    GLFWwindow *window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Textures2D");

    init_glad();
    //----------------init----------------

    Geometry *square = create_square();

    GLSLProgram *shader = new GLSLProgram();
    shader->compile_shaders_from_file("res/shaders/one_texture_affine_test.shader");
    shader->link();
    shader->use();

    unsigned int texture_1_slot = 15;
    Texture2D *texture_1 = new Texture2D("res/textures/metal_2.jpg", texture_1_slot);
    texture_1->bind(texture_1_slot);
    shader->set_uniform_1i("texture_1", texture_1_slot);

    // unsigned int texture_2_slot = 16;
    // Texture2D *texture_2 = new Texture2D("res/textures/wood.png", texture_2_slot);
    // texture_2->bind(texture_2_slot);
    // shader->set_uniform_1i("texture_2", texture_2_slot);

    const double fps_limit = 1.0f / 60.0f;
    double last_frame_time = 0;

    float alpha = 0.0f;
    float beta = 0.0f;
    float i = 1.0;

    while (!glfwWindowShouldClose(window)) // Loop until the user closes the window
    {
        double now = glfwGetTime();

        glfwPollEvents(); // Poll for and process events

        alpha += M_PI / 1000000.0;

        if (alpha > 2 * M_PI)
            alpha = 0.0f;

        shader->set_uniform_1f("value", alpha);

        if (beta > 1.0f)
            i = -1;
        else if (beta < 0.0f)
            i = 1;

        beta += 0.000001f * i;

        if ((now - last_frame_time) >= fps_limit)
        {
            glClearColor(0.2f, 0.3f, beta, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT);

            square->render();

            glfwSwapBuffers(window); // Swap front and back buffers

            last_frame_time = now;
        }
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

GLFWwindow *init_window(int width, int height, const char *name)
{
    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
    {
        std::cout << "Create window error.\n";
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    return window;
}