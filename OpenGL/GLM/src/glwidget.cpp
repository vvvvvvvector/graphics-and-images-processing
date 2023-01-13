#include "glwidget.h"

GLWidget::GLWidget()
{
}

void GLWidget::init_widget()
{
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
}