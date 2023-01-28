#include "glwidget.h"

GLWidget glwidget = GLWidget();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_press_callback(GLFWwindow *, int, int, int, int);
void mouse_move_callback(GLFWwindow *window, double xpos, double ypos);

int main(void)
{
    //----------------callbacks----------------
    glfwSetFramebufferSizeCallback(glwidget.glfw_window, framebuffer_size_callback);
    glfwSetKeyCallback(glwidget.glfw_window, key_press_callback);
    glfwSetCursorPosCallback(glwidget.glfw_window, mouse_move_callback);
    //----------------callbacks----------------

    //----------------init----------------
    const double fps_limit = 1.0 / 60.0;
    double last_frame_time = 0;
    //----------------init----------------

    // ----------------grass----------------
    float alpha = 0.0f;
    float beta = 0.0f;
    float gamma = 0.0f;

    int amount = 20;
    float offset = 0.5f;
    // ----------------grass----------------

    float blue_value = 0.0f;
    float i = 1.0;

    while (!glfwWindowShouldClose(glwidget.glfw_window)) // Loop until the user closes the window
    {
        double now = glfwGetTime();

        glfwPollEvents(); // Poll for and process events

        glwidget.viewMat = glwidget.main_camera.matrix();

        if (alpha > 2 * M_PI)
            alpha = 0.0f;

        alpha += M_PI / 750000.0f;

        if (beta > 2 * M_PI)
            beta = 0.0f;

        beta += M_PI / 500000.0f;

        if (gamma > 2 * M_PI)
            gamma = 0.0f;

        gamma += M_PI / 600000.0f;

        blue_value += 0.000001f * i;

        if ((now - last_frame_time) >= fps_limit)
        {
            glClearColor(0.2f, 0.3f, blue_value, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            for (float z = -amount, offset_z = -10.0f; z < amount; z += 2.0f, offset_z += offset)
            {
                for (float x = -amount, offset_x = 0.0f; x < amount; x += 2.0f, offset_x += offset)
                {
                    //--------grass 1--------
                    glwidget.shader["texture"]->use();

                    glwidget.frame["square"].pos = glm::vec4(offset_x, 0.0f, offset_z, 1.0f);
                    glwidget.frame["square"].forward = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

                    glwidget.shader["texture"]->set_uniform_1i("grass_texture", glwidget.texture_slot["grass"]);
                    glwidget.shader["texture"]->set_uniform_1f("angle", alpha);
                    glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
                    glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["square"].matrix());
                    glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

                    glwidget.geometry["square"]->render();
                    //--------grass 1--------

                    //--------grass 2--------
                    glwidget.shader["texture"]->use();

                    glwidget.frame["square"].pos = glm::vec4(offset_x, 0.0f, offset_z, 1.0f);
                    glwidget.frame["square"].forward = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

                    glwidget.shader["texture"]->set_uniform_1i("grass_texture", glwidget.texture_slot["grass"]);
                    glwidget.shader["texture"]->set_uniform_1f("angle", beta);
                    glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
                    glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["square"].matrix());
                    glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

                    glwidget.geometry["square"]->render();
                    //--------grass 2--------

                    //--------grass 3--------
                    glwidget.shader["texture"]->use();

                    glwidget.frame["square"].pos = glm::vec4(offset_x, 0.0f, offset_z, 1.0f);
                    glwidget.frame["square"].forward = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

                    glwidget.shader["texture"]->set_uniform_1i("grass_texture", glwidget.texture_slot["grass"]);
                    glwidget.shader["texture"]->set_uniform_1f("angle", gamma);
                    glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
                    glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["square"].matrix());
                    glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

                    glwidget.geometry["square"]->render();
                    //--------grass 3--------
                }
            }

            glfwSwapBuffers(glwidget.glfw_window); // Swap front and back buffers

            last_frame_time = now;
        }
    }

    glfwDestroyWindow(glwidget.glfw_window);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    float aspect = width / (float)height;

    glwidget.projMat = glm::perspective(30.0f, aspect, 0.1f, 10.0f);
}

void key_press_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    float speed = 0.75f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glwidget.main_camera.pos += speed * glwidget.main_camera.forward;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glwidget.main_camera.pos += speed * glwidget.main_camera.s();

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glwidget.main_camera.pos -= speed * glwidget.main_camera.forward;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glwidget.main_camera.pos -= speed * glwidget.main_camera.s();

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        glwidget.main_camera.pos += speed * glwidget.main_camera.up;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glwidget.main_camera.pos -= speed * glwidget.main_camera.up;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_move_callback(GLFWwindow *window, double xpos, double ypos)
{
    glm::vec4 camera_init_forward = glm::normalize(glm::vec4(0, 0, -1, 1));
    glwidget.main_camera.forward = glm::rotate(glwidget.identity, float(xpos / 100.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * camera_init_forward;

    glm::vec3 sx = glm::normalize(glwidget.main_camera.s());
    glwidget.main_camera.forward = glm::rotate(glwidget.identity, float(ypos / 100.0f), sx) * glm::vec4(glwidget.main_camera.forward, 1.0f);
}