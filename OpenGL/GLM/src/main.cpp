#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
#include "texture2d.h"
#include "mathgl.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

float zoom = 1.0f;
int pos_x = 0, pos_y = 0;

int init_glfw();
int init_glad();
GLFWwindow *init_window(int, int, const char *);

void framebuffer_size_callback(GLFWwindow *, int, int);
void mouse_move_callback(GLFWwindow *, double, double);
void scroll_callback(GLFWwindow *, double, double);

int main(void)
{
    //----------------init----------------
    init_glfw();
    GLFWwindow *window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "GLM");
    init_glad();

    const double fps_limit = 1.0 / 60.0;
    double last_frame_time = 0;

    glm::mat4 identity = glm::mat4(1.0);

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, scroll_callback);
    //----------------init----------------

    Geometry *square = create_square();
    Geometry *pyramid = create_pyramid();

    GLSLProgram *shader = new GLSLProgram();
    shader->compile_shaders_from_file("res/shaders/base.shader");
    shader->link();
    shader->use();

    // unsigned int texture_1_slot = 15;
    // Texture2D *texture_1 = new Texture2D("res/textures/metal_2.jpg", texture_1_slot);
    // texture_1->bind(texture_1_slot);
    // shader->set_uniform_1i("texture_1", texture_1_slot);

    // unsigned int texture_2_slot = 16;
    // Texture2D *texture_2 = new Texture2D("res/textures/wood.png", texture_2_slot);
    // texture_2->bind(texture_2_slot);
    // shader->set_uniform_1i("texture_2", texture_2_slot);

    float beta = 0.0f;
    float i = 1.0;

    while (!glfwWindowShouldClose(window)) // Loop until the user closes the window
    {
        double now = glfwGetTime();

        glfwPollEvents(); // Poll for and process events

        glm::mat4 viewMat = glm::mat4(1.0);
        viewMat *= glm::scale(identity, glm::vec3(zoom, zoom, zoom));
        viewMat *= glm::rotate(identity, pos_y / 100.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        viewMat *= glm::rotate(identity, pos_x / 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        shader->set_unifrom_4fv("MVMat", viewMat);

        if (beta > 1.0f)
            i = -1;
        else if (beta < 0.0f)
            i = 1;

        beta += 0.000001f * i;

        if ((now - last_frame_time) >= fps_limit)
        {
            glClearColor(0.2f, 0.3f, beta, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            pyramid->render();

            glfwSwapBuffers(window); // Swap front and back buffers

            last_frame_time = now;
        }
    }

    delete square;
    delete pyramid;

    glfwDestroyWindow(window);

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

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_move_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        return;

    pos_x = (int)xpos;
    pos_y = (int)ypos;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    zoom += yoffset / 1000.0f;
}