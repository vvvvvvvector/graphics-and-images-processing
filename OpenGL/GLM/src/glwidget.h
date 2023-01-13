#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <glad/glad.h>

#include <map>

#include "mathgl.h"
#include "glslprogram.h"
#include "geometry.h"
#include "texture2d.h"
#include "primitives.h"

class GLWidget
{
public:
    GLWidget();

    std::map<std::string, GLSLProgram *> shader;
    std::map<std::string, Geometry *> geometry;
    std::map<std::string, Texture2D *> texture;
    std::map<std::string, unsigned int> texture_slot;

    glm::mat4 viewMat;
    glm::mat4 projMat;

    void init_widget();

private:
    void create_shaders();
    void create_textures();
    void create_geometry();
};

#endif // GLWIDGET_H