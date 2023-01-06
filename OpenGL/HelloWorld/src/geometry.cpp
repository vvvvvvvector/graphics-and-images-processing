#include "geometry.h"

Geometry::Geometry()
{
    glGenVertexArrays(1, &vao);

    n_vertices = 0;
    n_indices = 0;
}

void Geometry::render()
{
    glBindVertexArray(vao);

    if (n_indices)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(mode, n_indices, GL_UNSIGNED_INT, (void *)0); // draw call
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        glDrawArrays(mode, 0, n_vertices); // draw call
    }

    glBindVertexArray(0);
}

void Geometry::set_indices(GLuint *data, int n)
{
    n_indices = n;

    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n * sizeof(GLuint), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geometry::set_attribute(unsigned int attributeIndex, vec2 *data, int n)
{
    if (attributesBuffer.find(attributeIndex) == attributesBuffer.end())
    {
        GLuint id;
        glGenBuffers(1, &id);
        attributesBuffer.insert({attributeIndex, id});
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, attributesBuffer[attributeIndex]);

    glBufferData(GL_ARRAY_BUFFER, n * sizeof(vec2), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeIndex, 2, GL_FLOAT, GL_FALSE, 0, (void *)0); // specifying layout of data here (each vertex is 2 floats, which in this array, are at a distance of 2 * sizeof(float) from each other)
    glEnableVertexAttribArray(attributeIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Geometry::set_attribute(unsigned int attributeIndex, vec3 *data, int n)
{
    if (attributesBuffer.find(attributeIndex) == attributesBuffer.end())
    {
        GLuint id;
        glGenBuffers(1, &id);
        attributesBuffer.insert({attributeIndex, id});
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, attributesBuffer[attributeIndex]);

    glBufferData(GL_ARRAY_BUFFER, n * sizeof(vec3), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeIndex, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // specifying layout of data here (each vertex is 2 floats, which in this array, are at a distance of 2 * sizeof(float) from each other)
    glEnableVertexAttribArray(attributeIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Geometry::set_attribute(unsigned int attributeIndex, vec4 *data, int n)
{
    if (attributesBuffer.find(attributeIndex) == attributesBuffer.end())
    {
        GLuint id;
        glGenBuffers(1, &id);
        attributesBuffer.insert({attributeIndex, id});
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, attributesBuffer[attributeIndex]);

    glBufferData(GL_ARRAY_BUFFER, n * sizeof(vec4), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeIndex, 4, GL_FLOAT, GL_FALSE, 0, (void *)0); // specifying layout of data here (each vertex is 2 floats, which in this array, are at a distance of 2 * sizeof(float) from each other)
    glEnableVertexAttribArray(attributeIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Geometry::set_vertices(unsigned int attributeIndex, vec2 *vertices, int n)
{
    n_vertices = n;
    set_attribute(attributeIndex, vertices, n);
}