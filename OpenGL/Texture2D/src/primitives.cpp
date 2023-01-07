#include "primitives.h"

Geometry *create_main_axes()
{
    Geometry *geometry = new Geometry();

    vec2 positions[] = {
        {0.0f, 0.0f},
        {0.5f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.5f},
        {0.0f, 0.0f},
        {-0.30f, -0.30f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f}};

    geometry->mode = GL_LINES;

    geometry->set_vertices(0, positions, 6);
    geometry->set_attribute(1, colors, 6);

    return geometry;
}

Geometry *create_triangle()
{
    vec2 positions[] = {
        {0.0f, 0.0f},
        {0.5f, 0.0f},
        {0.0f, 0.5f},
        {0.5f, 0.5f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.2f, 0.5f, 1.0f, 1.0f}};

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 3;
    GLuint indices[size] = {1, 0, 3};
    geometry->set_indices(indices, size);

    geometry->set_vertices(0, positions, 4);
    geometry->set_attribute(1, colors, 4);

    return geometry;
}

Geometry *create_square()
{
    vec2 positions[] = {
        {0.0f, 0.0f},
        {0.8f, 0.0f},
        {0.0f, 0.8f},
        {0.8f, 0.8f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.2f, 0.5f, 1.0f, 1.0f}};

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 6;
    GLuint indices[size] = {0, 1, 2, 2, 3, 1};
    geometry->set_indices(indices, size);

    geometry->set_vertices(0, positions, 4);
    geometry->set_attribute(1, colors, 4);

    return geometry;
}