#include "glwidget.h"

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;

GLWidget::GLWidget()
{
    init_widget();

    identity = glm::mat4(1.0f);
    projMat = glm::perspective(30.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10.0f);
}

void GLWidget::init_widget()
{
    init_glfw();
    init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Refactor");
    init_glad();

    create_shaders();
    create_geometry();
    create_textures();
}

void GLWidget::create_shaders()
{
    shader["basic"] = new GLSLProgram();
    shader["basic"]->compile_shaders_from_file("res/shaders/base.shader");
    shader["basic"]->link();

    shader["texture"] = new GLSLProgram();
    shader["texture"]->compile_shaders_from_file("res/shaders/one_texture.shader");
    shader["texture"]->link();
}

void GLWidget::create_geometry()
{
    geometry["pyramid"] = create_pyramid();

    geometry["square"] = create_square();
    frame["square"] = new Frame();

    geometry["axes"] = create_main_axes();
}

void GLWidget::create_textures()
{
    texture_slot["wood"] = 15;
    texture["wood"] = new Texture2D("res/textures/wood.jpg", texture_slot["wood"]);
    texture["wood"]->bind(texture_slot["wood"]);

    texture_slot["moon"] = 16;
    texture["moon"] = new Texture2D("res/textures/moon.jpg", texture_slot["moon"]);
    texture["moon"]->bind(texture_slot["moon"]);

    texture_slot["lenna"] = 17;
    texture["lenna"] = new Texture2D("res/textures/lenna.png", texture_slot["lenna"]);
    texture["lenna"]->bind(texture_slot["lenna"]);
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