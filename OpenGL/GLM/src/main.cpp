#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glwidget.h"

GLWidget widget = GLWidget();

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;

glm::mat4 projMat = glm::perspective(60.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10.0f);

int init_glfw();
int init_glad();
GLFWwindow *init_window(int, int, const char *);

void framebuffer_size_callback(GLFWwindow *, int, int);
void key_callback(GLFWwindow *, int, int, int, int);

int main(void)
{
    //----------------init----------------
    init_glfw();
    GLFWwindow *window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "GLM");
    init_glad();

    const double fps_limit = 1.0 / 60.0;
    double last_frame_time = 0;

    glm::mat4 identity = glm::mat4(1.0f);

    widget.init_widget();

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    //----------------init----------------

    float alpha = 0.0f;

    float blue_value = 0.0f;
    float i = 1.0;

    while (!glfwWindowShouldClose(window)) // Loop until the user closes the window
    {
        double now = glfwGetTime();

        glfwPollEvents(); // Poll for and process events

        glm::mat4 viewMat = widget.main_camera->matrix();

        if (alpha > 2 * M_PI)
            alpha = 0.0f;

        alpha += M_PI / 750000.0f;

        if (blue_value > 1.0f)
            i = -1;
        else if (blue_value < 0.0f)
            i = 1;

        blue_value += 0.000001f * i;

        if ((now - last_frame_time) >= fps_limit)
        {
            glClearColor(0.2f, 0.3f, blue_value, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //--------figure 1--------
            widget.shader["texture"]->use();

            glm::mat4 R = glm::rotate(identity, alpha, glm::vec3(0.0f, 0.0f, 1.0f));
            widget.frame["square"]->pos = R * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

            widget.shader["texture"]->set_uniform_1i("texture_1", widget.texture_slot["lenna"]);
            widget.shader["texture"]->set_unifrom_4fv("MVMat", viewMat * widget.frame["square"]->matrix());
            widget.shader["texture"]->set_unifrom_4fv("ProjMat", projMat);

            widget.geometry["square"]->render();
            //--------figure 1--------

            //--------figure 2--------
            widget.shader["basic"]->use();

            widget.shader["basic"]->set_unifrom_4fv("MVMat", viewMat);
            widget.shader["basic"]->set_unifrom_4fv("ProjMat", projMat);

            widget.geometry["axes"]->render();
            //--------figure 2--------

            glfwSwapBuffers(window); // Swap front and back buffers

            last_frame_time = now;
        }
    }

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

    float aspect = width / (float)height;

    projMat = glm::perspective(60.0f, aspect, 0.1f, 10.0f);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        widget.main_camera->pos += 0.1f * widget.main_camera->forward;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        widget.main_camera->pos += 0.1f * widget.main_camera->s();

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        widget.main_camera->pos -= 0.1f * widget.main_camera->forward;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        widget.main_camera->pos -= 0.1f * widget.main_camera->s();
}