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

    //----------by indexes----------
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, n_indices, GL_UNSIGNED_INT, (void *)0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //----------by indexes----------

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

void Geometry::set_attribute(unsigned int attibuteIndex, vec2 *data, int n)
{
    if (attributesBuffer.find(attibuteIndex) == attributesBuffer.end())
    {
        GLuint id;
        glGenBuffers(1, &id);
        attributesBuffer.insert({attibuteIndex, id});
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, attributesBuffer[attibuteIndex]);

    glBufferData(GL_ARRAY_BUFFER, n * sizeof(vec2), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attibuteIndex, 2, GL_FLOAT, GL_FALSE, 0, (void *)0); // specifying layout of data here (each vertex is 2 floats, which in this array, are at a distance of 2 * sizeof(float) from each other)
    glEnableVertexAttribArray(attibuteIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Geometry::set_attribute(unsigned int attibuteIndex, vec4 *data, int n)
{
    if (attributesBuffer.find(attibuteIndex) == attributesBuffer.end())
    {
        GLuint id;
        glGenBuffers(1, &id);
        attributesBuffer.insert({attibuteIndex, id});
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, attributesBuffer[attibuteIndex]);

    glBufferData(GL_ARRAY_BUFFER, n * sizeof(vec4), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attibuteIndex, 4, GL_FLOAT, GL_FALSE, 0, (void *)0); // specifying layout of data here (each vertex is 2 floats, which in this array, are at a distance of 2 * sizeof(float) from each other)
    glEnableVertexAttribArray(attibuteIndex);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Geometry::set_vertices(unsigned int attibuteIndex, vec2 *vertices, int n)
{
    n_vertices = n;
    set_attribute(attibuteIndex, vertices, n);
}

void Geometry::set_vertices(unsigned int attibuteIndex, vec4 *vertices, int n)
{
    set_attribute(attibuteIndex, vertices, n);
}