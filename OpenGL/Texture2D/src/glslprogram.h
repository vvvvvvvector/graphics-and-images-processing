#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

class GLSLProgram
{
private:
    GLuint program;

    GLuint compile_shader(GLuint type, const std::string &source);

public:
    GLSLProgram();
    ~GLSLProgram();

    void compile_shaders_from_file(const std::string &filepath);

    void link();
    void use();

    void set_uniform(const char *name, int value);
};

#endif // GLSLPROGRAM_H