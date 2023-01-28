#include "frame.h"

Frame::Frame()
{
    pos = glm::vec3(0, 0, 0);
    forward = glm::vec3(0, 0, 1);
    up = glm::vec3(0, 1, 0);
}

glm::vec3 Frame::s()
{
    return glm::normalize(glm::cross(up, forward));
}

glm::mat4 Frame::matrix()
{
    glm::mat4 mat = glm::mat4(0.0f);
    glm::vec3 xx = s();
    glm::vec3 f_norm = glm::normalize(forward);
    glm::vec3 u_norm = glm::normalize(up);

    mat[0][0] = xx.x;
    mat[1][0] = u_norm.x;
    mat[2][0] = f_norm.x;

    mat[0][1] = xx.y;
    mat[1][1] = u_norm.y;
    mat[2][1] = f_norm.y;

    mat[0][2] = xx.z;
    mat[1][2] = u_norm.z;
    mat[2][2] = f_norm.z;

    mat[3][3] = 1.0f;

    return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z)) * mat;
}