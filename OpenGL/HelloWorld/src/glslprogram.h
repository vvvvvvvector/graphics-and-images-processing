#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <glad/glad.h>

#include <iostream>

class GLSLProgram
{
private:
    GLuint program;

    GLuint compile_shader(GLuint type, const std::string &source);

public:
    GLSLProgram();

    void compile_shaders_from_file(const std::string &filepath);

    void link();
    void use();
    void delete_program();
};

#endif // GLSLPROGRAM_H