#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "mathgl.h"

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    void compile_shaders_from_file(const std::string &filepath);

    void link();
    void use();

    void set_uniform_1i(const char *name, int value);
    void set_uniform_1f(const char *name, float value);
    void set_unifrom_4fv(const char *name, glm::mat4 mat);
    void set_uniform_vec3(const char *name, glm::vec3 vec);
    void set_uniform_vec4(const char *name, glm::vec4 vec);

private:
    GLuint program;

    GLuint compile_shader(GLuint type, const std::string &source);
};

#endif // GLSLPROGRAM_H