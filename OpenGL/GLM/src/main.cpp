#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
#include "texture2d.h"
#include "mathgl.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

float zoom = 0.75f;
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

    Geometry *pyramid = create_pyramid();
    Geometry *square = create_square();
    Geometry *axes = create_main_axes();

    GLSLProgram *basic_shader = new GLSLProgram();
    basic_shader->compile_shaders_from_file("res/shaders/base.shader");
    basic_shader->link();

    GLSLProgram *texture_shader = new GLSLProgram();
    texture_shader->compile_shaders_from_file("res/shaders/one_texture.shader");
    texture_shader->link();

    unsigned int texture_1_slot = 15;
    Texture2D *texture_1 = new Texture2D("res/textures/earth.jpg", texture_1_slot);
    texture_1->bind(texture_1_slot);

    unsigned int texture_2_slot = 16;
    Texture2D *texture_2 = new Texture2D("res/textures/moon.jpg", texture_2_slot);
    texture_2->bind(texture_2_slot);

    float alpha = 0.0f;
    float beta = 0.0f;
    float gamma = 0.0f;

    float blue_value = 0.0f;
    float i = 1.0;

    while (!glfwWindowShouldClose(window)) // Loop until the user closes the window
    {
        double now = glfwGetTime();

        glfwPollEvents(); // Poll for and process events

        glm::mat4 viewMat = glm::mat4(1.0);
        viewMat *= glm::scale(identity, glm::vec3(zoom, zoom, zoom));
        viewMat *= glm::rotate(identity, pos_y / 100.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        viewMat *= glm::rotate(identity, pos_x / 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        if (alpha > 2 * M_PI)
            alpha = 0.0f;

        alpha += M_PI / 100000.0f;

        if (beta > 2 * M_PI)
            beta = 0.0f;

        beta += M_PI / 75000.0f;

        if (gamma > 2 * M_PI)
            gamma = 0.0f;

        gamma += M_PI / 80000.0f;

        if (blue_value > 1.0f)
            i = -1;
        else if (blue_value < 0.0f)
            i = 1;

        blue_value += 0.000001f * i;

        if ((now - last_frame_time) >= fps_limit)
        {
            glClearColor(0.2f, 0.3f, blue_value, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //--------figure 2--------
            texture_shader->use();
            texture_shader->set_uniform_1i("texture_1", texture_1_slot);

            glm::mat4 square_1_mat = identity;
            glm::mat4 R = glm::rotate(identity, alpha, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 T = glm::translate(identity, glm::vec3(1.0f, 0.0f, -0.5f));
            glm::mat4 R_reverse = glm::rotate(identity, -alpha, glm::vec3(0.0f, 0.0f, 1.0f));

            square_1_mat = glm::scale(identity, glm::vec3(0.75f, 0.75f, 0.75f)) * R * T * R_reverse;

            texture_shader->set_unifrom_4fv("MVMat", viewMat * square_1_mat);

            square->render();
            //--------figure 2--------

            //--------figure 1--------
            texture_shader->use();

            texture_shader->set_uniform_1i("texture_1", texture_2_slot);

            glm::mat4 square_2_mat = identity;

            square_2_mat = glm::scale(identity, glm::vec3(0.45f, 0.45f, 0.45f)) * glm::rotate(identity, gamma, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(identity, glm::vec3(3.0f, 0.0f, -0.5f)) * glm::rotate(identity, -gamma, glm::vec3(0.0f, 0.0f, 1.0f));

            texture_shader->set_unifrom_4fv("MVMat", viewMat * square_1_mat * square_2_mat);

            square->render();
            //--------figure 1--------

            //--------figure 3--------
            basic_shader->use();

            glm::mat4 pyramid_mat = identity;
            glm::mat4 S = glm::scale(identity, glm::vec3(0.55f, 0.55f, 0.55f));
            glm::mat4 R_pyramid = glm::rotate(identity, beta, glm::vec3(0.0f, 0.0f, 1.0f));

            pyramid_mat = S * R_pyramid;

            basic_shader->set_unifrom_4fv("MVMat", viewMat * pyramid_mat);

            pyramid->render();
            //--------figure 3--------

            //--------figure 4--------
            basic_shader->use();

            basic_shader->set_unifrom_4fv("MVMat", viewMat);

            axes->render();
            //--------figure 4--------

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