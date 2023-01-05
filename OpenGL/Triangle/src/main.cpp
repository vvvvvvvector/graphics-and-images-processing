#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

const unsigned int window_width = 500;
const unsigned int window_height = 500;

struct ShadersSource
{
    std::string vertex;
    std::string fragment;
};

static ShadersSource parse_shaders(const std::string &filepath)
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

static GLuint compile_shader(GLuint type, const std::string &source)
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

static GLuint create_shader(const std::string &vertex_shader, const std::string &fragment_shader)
{
    GLuint program = glCreateProgram();

    GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);     // file_1
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader); // file_2

    // linking file_1 and file_2 in one program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    if (!glfwInit())
    {
        std::cout << "glfw init error.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Triangle", NULL, NULL);
    if (!window)
    {
        std::cout << "Create window error.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        return -1;
    }

    float positions[] = {
        0.0f, 0.0f,
        0.5f, 0.0f,
        0.0f, 0.5f};

    GLuint vbo, vao; // id for my buffer

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo); // generating id for my buffer

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo); // selecting my buffer; work on this buffer

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0); // configure attribute
    glEnableVertexAttribArray(0);                                                  // fire this attribute(position, texture, ...)

    glBindBuffer(GL_ARRAY_BUFFER, 0); // unselect my buffer

    glBindVertexArray(0);

    ShadersSource shaders = parse_shaders("res/shaders/basic.shader");

    GLuint shader = create_shader(shaders.vertex, shaders.fragment);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);           // its like glBegin?
        glDrawArrays(GL_TRIANGLES, 0, 3); // draw call -> should draw a triangle
        glBindVertexArray(0);             // its like glEnd?

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);

    glfwTerminate();

    return 0;
}