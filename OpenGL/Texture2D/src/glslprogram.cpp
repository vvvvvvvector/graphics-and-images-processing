#include "glslprogram.h"

GLSLProgram::GLSLProgram()
{
    program = glCreateProgram();
}

struct ShaderStrings
{
    std::string vertex;
    std::string fragment;
};

ShaderStrings parse_shaders_from_file(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

GLuint GLSLProgram::compile_shader(GLuint type, const std::string &source)
{
    GLuint id = glCreateShader(type);
    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char)); // because message[length] doesnt work
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader!\n";
        std::cout << message << '\n';
        glDeleteShader(id);
        return -1;
    }

    return id;
}

void GLSLProgram::compile_shaders_from_file(const std::string &filepath)
{
    ShaderStrings shaders = parse_shaders_from_file(filepath);

    GLuint vs = compile_shader(GL_VERTEX_SHADER, shaders.vertex);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, shaders.fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void GLSLProgram::link()
{
    glLinkProgram(program);
}

void GLSLProgram::use()
{
    glUseProgram(program);
}

void GLSLProgram::set_uniform(const char *name, int value)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc != -1)
        glUniform1i(loc, value);
}