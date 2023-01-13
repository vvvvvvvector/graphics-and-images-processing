#ifndef MATHGL_H
#define MATHGL_H

#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Frame
{
public:
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;

    Frame()
    {
        pos = glm::vec3(0, 0, 0);
        forward = glm::vec3(0, 0, -1);
        up = glm::vec3(0, 1, 0);
    }

    virtual glm::vec3 s()
    {
        return glm::normalize(glm::cross(up, forward));
    }

    virtual glm::mat4 matrix()
    {
        glm::mat4 mat = glm::mat4(1.0);
        glm::vec3 xx = s();
        glm::vec3 f_norm = glm::normalize(forward);
        glm::vec3 u_norm = glm::normalize(up);

        mat[0] = glm::vec4(xx, 0.0);
        mat[1] = glm::vec4(u_norm, 0.0);
        mat[2] = glm::vec4(f_norm, 0.0);
        mat[3] = glm::vec4(pos, 1.0);

        return mat;
    }
};

class Camera : public Frame
{
public:
    Camera()
    {
        pos = glm::vec3(0, 0, 1);
        forward = glm::vec3(0, 0, -1);
        up = glm::vec3(0, 1, 0);
    }

    glm::vec3 s()
    {
        return glm::normalize(glm::cross(up, forward));
    }

    glm::mat4 matrix()
    {
        glm::mat4 mat = glm::mat4(1.0);
        glm::vec3 xx = s();
        glm::vec3 f_norm = glm::normalize(forward);
        glm::vec3 u_norm = glm::normalize(up);

        mat[0][0] = xx.x;
        mat[1][0] = xx.y;
        mat[2][0] = xx.z;

        mat[0][1] = u_norm.x;
        mat[1][1] = u_norm.y;
        mat[2][1] = u_norm.z;

        mat[0][2] = -f_norm.x;
        mat[1][2] = -f_norm.y;
        mat[2][2] = -f_norm.z;

        mat *= glm::translate(glm::mat4(1.0f), glm::vec3(-pos.x, -pos.y, -pos.z));

        return mat;
    }
};

#endif // MATHGL_H