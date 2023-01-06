#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>

#include "mathgl.h"

#include <iostream>
#include <map>

class Geometry
{
private:
    GLuint vao;

    GLuint ibo;

    unsigned int n_vertices;
    unsigned int n_indices;

    std::map<unsigned int, GLuint> attributesBuffer;

    void set_attribute(unsigned int attributeIndex, vec2 *data, int n);

    void set_attribute(unsigned int attributeIndex, vec4 *data, int n);

public:
    Geometry();

    void render();

    void set_indices(GLuint *data, int n);

    void set_vertices(unsigned int attributeIndex, vec2 *vertices, int n);

    void set_vertices(unsigned int attributeIndex, vec4 *vertices, int n);
};

#endif // GEOMETRY_H