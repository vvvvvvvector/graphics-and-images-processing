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