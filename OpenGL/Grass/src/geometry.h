#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>

#include <iostream>
#include <map>

#include "mathgl.h"
#include "utils.h"

class Geometry
{
public:
    Geometry();

    GLenum mode;

    void render();

    void set_indices(GLuint *data, int n);

    void set_vertices(unsigned int attributeIndex, glm::vec3 *vertices, int n);

    void set_attribute(unsigned int attributeIndex, glm::vec2 *data, int n);
    void set_attribute(unsigned int attributeIndex, glm::vec3 *data, int n);
    void set_attribute(unsigned int attributeIndex, glm::vec4 *data, int n);

private:
    GLuint vao;

    GLuint ibo;

    unsigned int n_vertices;
    unsigned int n_indices;

    std::map<unsigned int, GLuint> attributesBuffer;
};

#endif // GEOMETRY_H