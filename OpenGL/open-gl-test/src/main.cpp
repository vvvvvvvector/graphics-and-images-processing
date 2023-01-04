#include <GLFW/glfw3.h>

#include <vector>

struct vec3
{
    float x, y, z;
};

struct vec4
{
    float r, g, b, alpha;
};

vec3 points[] = {
    {0.0f, 0.0f, 0.0f},
    {0.5f, 0.0f, 0.0f},
    {0.0f, 0.5f, 0.0f}};

vec4 colors[] = {
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {0.0f, 0.7f, 1.0f, 1.0f},
};

void triangle()
{
    glVertexPointer(3, GL_FLOAT, 0, &points);

    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(4, GL_FLOAT, 0, &colors);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

vec3 cube_points[] = {
    {0, 0, 0},
    {0, 0.2, 0},
    {0.2, 0, 0},
    {0.2, 0.2, 0},
    {0, 0, 0.2},
    {0, 0.2, 0.2},
    {0.2, 0, 0.2},
    {0.2, 0.2, 0.2},
};

GLuint indexes_1[] = {0, 1, 2, 2, 3, 1};
GLuint indexes_2[] = {0, 4, 5, 0, 1, 5};
GLuint indexes_3[] = {0, 2, 6, 0, 4, 6};
GLuint indexes_4[] = {2, 3, 7, 2, 6, 7};
GLuint indexes_5[] = {1, 3, 7, 1, 5, 7};
GLuint indexes_6[] = {4, 6, 7, 4, 5, 7};

void coordinate_system_with_cube()
{
    glRotatef(1, 1, 1, 1);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.5f);
    glEnd();

    glVertexPointer(3, GL_FLOAT, 0, &cube_points);

    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.3, 0.7, 0.8);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indexes_1);
    glColor3f(0.0, 0.7, 0.4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indexes_2);
    glColor3f(0.1, 0.1, 0.4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indexes_3);
    glColor3f(0.9, 0.0, 0.2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indexes_4);
    glColor3f(0.0, 0.9, 0.8);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indexes_5);
    glColor3f(0.9, 0.9, 0.25);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indexes_6);

    glDisableClientState(GL_VERTEX_ARRAY);
}

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        coordinate_system_with_cube();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}