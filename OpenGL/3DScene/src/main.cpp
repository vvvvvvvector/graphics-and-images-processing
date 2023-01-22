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

    //----------------light----------------
    glm::vec3 normals[] = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}};

    glm::vec3 light_position(0.0f, 0.0f, 0.0f);
    glm::vec4 light_color(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec4 material_color_ads(0.35f, 0.6f, 0.75f, 1.0f);
    glm::vec4 material_color_ads_per_fragment(0.35f, 0.2f, 0.34f, 1.0f);
    //----------------light----------------

    float alpha = 0.0f;
    float beta = 0.0f;
    float gamma = 0.0f;
    float teta = 0.0f;

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

        if (teta > 2 * M_PI)
            teta = 0.0f;

        teta += M_PI / 550000.0f;

        if (blue_value > 1.0f)
            i = -1;
        else if (blue_value < 0.0f)
            i = 1;

        blue_value += 0.000001f * i;

        if ((now - last_frame_time) >= fps_limit)
        {
            glClearColor(0.2f, 0.3f, blue_value, 0.9f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            //--------object 1--------
            glwidget.shader["texture"]->use();

            glwidget.frame["square"].pos = glm::vec4(0.0f, 0.0f, -7.0f, 1.0f);

            glwidget.shader["texture"]->set_uniform_1i("texture_1", glwidget.texture_slot["metal"]);
            glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["square"].matrix());
            glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["square"]->render();
            //--------object 1--------

            //--------object 2--------
            glwidget.shader["texture"]->use();

            glwidget.frame["square"].pos = glm::vec4(-2.0f, 0.0f, -7.0f, 1.0f);

            glwidget.shader["texture"]->set_uniform_1i("texture_1", glwidget.texture_slot["lenna"]);
            glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["square"].matrix());
            glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["square"]->render();
            //--------object 2--------

            //--------object 3--------
            glwidget.shader["basic"]->use();

            glwidget.frame["axes"].pos = glm::vec4(-2.0f, 0.0f, -3.0f, 1.0f);

            glwidget.shader["basic"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["basic"]->set_unifrom_4fv("ModelMat", glwidget.frame["axes"].matrix());
            glwidget.shader["basic"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["axes"]->render();
            //--------object 3--------

            //--------object 4--------
            glwidget.shader["basic"]->use();

            glwidget.frame["pyramid"].pos = glm::vec4(-3.0f, 0.0f, -4.2f, 1.0f);
            glwidget.frame["pyramid"].forward = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            glwidget.frame["pyramid"].up = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);

            glwidget.shader["basic"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["basic"]->set_unifrom_4fv("ModelMat", glwidget.frame["pyramid"].matrix());
            glwidget.shader["basic"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["pyramid"]->render();
            //--------object 4--------

            //--------object 5--------
            glwidget.shader["texture"]->use();

            glwidget.frame["square"].pos = glm::vec4(1.5f, 1.2f, -5.0f, 1.0f);

            glwidget.shader["texture"]->set_uniform_1i("texture_1", glwidget.texture_slot["grass"]);
            glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["square"].matrix());
            glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["square"]->render();
            //--------object 5--------

            //--------object 6--------
            glwidget.shader["texture"]->use();

            glm::mat4 rotate_earth_orbit = glm::rotate(glwidget.identity, alpha, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 rotate_earth = glm::rotate(glwidget.identity, beta, glm::vec3(1.0f, 1.0f, 0.0f));

            glwidget.frame["earth"].pos = rotate_earth_orbit * glm::vec4(1.5, 0.0f, -2.8f, 1.0f);
            glwidget.frame["earth"].up = rotate_earth * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            glwidget.shader["texture"]->set_uniform_1i("texture_1", glwidget.texture_slot["earth"]);
            glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["earth"].matrix());
            glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["square"]->render();
            //--------object 6--------

            //--------object 7--------
            glwidget.shader["texture"]->use();

            glm::mat4 scale_moon = glm::scale(glwidget.identity, glm::vec3(0.55f, 0.55f, 0.55f));
            glm::mat4 rotate_moon_orbit = glm::rotate(glwidget.identity, gamma, glm::vec3(0.0f, 0.0f, 1.0f));

            glwidget.frame["moon"].pos = glm::vec4(glwidget.frame["earth"].pos, 1.0) + rotate_moon_orbit * glm::vec4(1.5, 0.0f, 0.0f, 1.0f);

            glwidget.shader["texture"]->set_uniform_1i("texture_1", glwidget.texture_slot["moon"]);
            glwidget.shader["texture"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["texture"]->set_unifrom_4fv("ModelMat", glwidget.frame["moon"].matrix() * scale_moon);
            glwidget.shader["texture"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["square"]->render();
            //--------object 7--------

            //--------object 8--------
            glwidget.shader["ads"]->use();

            glm::mat4 rotate_light_square = glm::rotate(glwidget.identity, teta, glm::vec3(0, 0, 1));
            glwidget.frame["light_ads"].pos = glm::vec4(-3.5f, 0.0f, -1.0f, 1.0f);
            glwidget.frame["light_ads"].up = rotate_light_square * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

            glwidget.shader["ads"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["ads"]->set_unifrom_4fv("ModelMat", glwidget.frame["light_ads"].matrix());
            glwidget.shader["ads"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.shader["ads"]->set_uniform_vec3("LightPosition", light_position);
            glwidget.shader["ads"]->set_uniform_vec4("LightColor", light_color);
            glwidget.shader["ads"]->set_uniform_vec4("MaterialColor", material_color_ads);

            glwidget.geometry["light_ads"]->set_attribute(2, normals, 4);

            glwidget.geometry["light_ads"]->render();
            //--------object 8--------

            //--------object 9--------
            glwidget.shader["ads_per_fragment"]->use();

            glwidget.frame["light_ads_per_fragment"].pos = glm::vec4(-1.5f, 0.0f, -1.0f, 1.0f);
            glwidget.frame["light_ads_per_fragment"].up = rotate_light_square * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

            glwidget.shader["ads_per_fragment"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["ads_per_fragment"]->set_unifrom_4fv("ModelMat", glwidget.frame["light_ads_per_fragment"].matrix());
            glwidget.shader["ads_per_fragment"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.shader["ads_per_fragment"]->set_uniform_vec3("LightPosition", light_position);
            glwidget.shader["ads_per_fragment"]->set_uniform_vec4("LightColor", light_color);
            glwidget.shader["ads_per_fragment"]->set_uniform_vec4("MaterialColor", material_color_ads_per_fragment);

            glwidget.geometry["light_ads_per_fragment"]->set_attribute((int)Attributes::normal, normals, 4);

            glwidget.geometry["light_ads_per_fragment"]->render();
            //--------object 9--------

            //--------object 9--------
            glwidget.shader["basic"]->use();

            glwidget.frame["cube"].pos = glm::vec4(-4.75f, 0.0f, -4.2f, 1.0f);

            glwidget.shader["basic"]->set_unifrom_4fv("ViewMat", glwidget.viewMat);
            glwidget.shader["basic"]->set_unifrom_4fv("ModelMat", glwidget.frame["cube"].matrix());
            glwidget.shader["basic"]->set_unifrom_4fv("ProjMat", glwidget.projMat);

            glwidget.geometry["cube"]->render();
            //--------object 9--------

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
    float speed = 0.25f;

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