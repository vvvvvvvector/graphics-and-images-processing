#include "glwidget.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

GLWidget::GLWidget()
{
    init_widget();

    identity = glm::mat4(1.0f);

    projMat = glm::perspective(30.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 25.0f);
}

void GLWidget::init_widget()
{
    init_glfw();
    init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "GrassRendering");
    init_glad();

    create_shaders();
    create_geometry();
    create_textures();
}

void GLWidget::create_shaders()
{
    shader["texture"] = new GLSLProgram();
    shader["texture"]->compile_shaders_from_file("res/shaders/texture.shader");
    shader["texture"]->link();
}

void GLWidget::create_geometry()
{
    geometry["square"] = create_square();
    frame["square"] = Frame();
}

void GLWidget::create_textures()
{
    texture_slot["grass"] = 20;
    texture["grass"] = new Texture2D("res/textures/grass_1.png", texture_slot["grass"]);
    texture["grass"]->bind(texture_slot["grass"]);
}

int GLWidget::init_glfw()
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

int GLWidget::init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        return -1;
    }

    return 0;
}

void GLWidget::init_window(int width, int height, const char *name)
{
    glfw_window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!glfw_window)
    {
        std::cout << "Create window error.\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(glfw_window);
}