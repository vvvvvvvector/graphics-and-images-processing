#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glslprogram.h"
#include "primitives.h"
#include "texture2d.h"
#include "mathgl.h"

#include <set>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

float zoom = 0.75f;
int pos_x = 0, pos_y = 0;

Camera main_camera = Camera();

glm::mat4 projMat = glm::mat4(1.0);

int init_glfw();
int init_glad();
GLFWwindow *init_window(int, int, const char *);

void framebuffer_size_callback(GLFWwindow *, int, int);
void mouse_move_callback(GLFWwindow *, double, double);
void scroll_callback(GLFWwindow *, double, double);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        std::cout << "w\n";
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        std::cout << "s\n";
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        std::cout << "a\n";
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        std::cout << "d\n";
    }
}

void process_camera()
{
    // main_camera.up = Rot_S(pos_y) * main_camera.up;
    // main_camera.forward = Rot_up(pos_x) * main_camera.forward;
}

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
    glfwSetKeyCallback(window, key_callback);
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

    float blue_value = 0.0f;
    float i = 1.0;

    Frame *square_frame = new Frame();

    Camera *main_camera = new Camera();

    while (!glfwWindowShouldClose(window)) // Loop until the user closes the window
    {
        double now = glfwGetTime();

        glfwPollEvents(); // Poll for and process events

        process_camera();
        glm::mat4 viewMat = main_camera->matrix();
        // viewMat *= glm::scale(identity, glm::vec3(zoom, zoom, zoom));
        // viewMat *= glm::rotate(identity, pos_y / 100.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        // viewMat *= glm::rotate(identity, pos_x / 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        // viewMat = glm::translate(identity, glm::vec3(0.0f, 0.0f, -0.5f));

        if (alpha > 2 * M_PI)
            alpha = 0.0f;

        alpha += M_PI / 100000.0f;

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
            texture_shader->use();

            glm::mat4 R = glm::rotate(identity, alpha, glm::vec3(0.0f, 0.0f, 1.0f));

            square_frame->pos = R * glm::vec4(1.0, 0.0, 0.0, 1.0);
            square_frame->up = glm::vec4(0.0, 1.0, 0.0, 1.0);

            texture_shader->set_uniform_1i("texture_1", texture_1_slot);
            texture_shader->set_unifrom_4fv("MVMat", viewMat * square_frame->matrix());
            texture_shader->set_unifrom_4fv("ProjMat", projMat);

            square->render();
            //--------figure 1--------

            //--------figure 1--------
            basic_shader->use();

            basic_shader->set_unifrom_4fv("MVMat", viewMat);

            axes->render();
            //--------figure 1--------

            glfwSwapBuffers(window); // Swap front and back buffers

            last_frame_time = now;
        }
    }

    delete square;
    delete pyramid;
    delete axes;

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

    // projMat = glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    projMat = glm::perspective(60.0f, aspect, 0.1f, 10.0f);
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