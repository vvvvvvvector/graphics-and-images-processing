#ifndef FRAME_H
#define FRAME_H

#include "mathgl.h"

class Frame
{
public:
    Frame();

    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;

    glm::vec3 s();
    glm::mat4 matrix();
};

#endif // FRAME_H