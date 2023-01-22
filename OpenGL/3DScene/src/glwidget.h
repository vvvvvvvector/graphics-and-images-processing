#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

#include "mathgl.h"
#include "glslprogram.h"
#include "geometry.h"
#include "texture2d.h"
#include "builder.h"
#include "frame.h"
#include "camera.h"

class GLWidget
{
public:
    GLWidget();

    std::map<std::string, GLSLProgram *> shader;

    std::map<std::string, Geometry *> geometry;
    std::map<std::string, Frame> frame;

    std::map<std::string, Texture2D *> texture;
    std::map<std::string, unsigned int> texture_slot;

    glm::mat4 viewMat;
    glm::mat4 projMat;

    glm::mat4 identity;

    Camera main_camera;

    // ----------glfw----------
    GLFWwindow *glfw_window;
    // ----------glfw----------

private:
    void create_shaders();
    void create_textures();
    void create_geometry();

    // ----------init----------
    int init_glfw();
    int init_glad();
    void init_window(int, int, const char *);
    void init_widget();
    // ----------init----------
};

#endif // GLWIDGET_H