#ifndef CAMERA_H
#define CAMERA_H

#include "mathgl.h"

class Camera
{
public:
    Camera();

    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;

    glm::vec3 s();
    glm::mat4 matrix();
};

#endif // CAMERA_H