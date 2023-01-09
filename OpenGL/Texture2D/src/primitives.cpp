#include "primitives.h"

Geometry *create_main_axes()
{
    Geometry *geometry = new Geometry();

    vec3 positions[] = {
        {0.0f, 0.0f, 0.0f},
        {0.7f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.7f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.7f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.7f, 0.5f, 1.0f, 1.0f},
        {0.7f, 0.5f, 1.0f, 1.0f}};

    geometry->mode = GL_LINES;

    geometry->set_vertices(0, positions, 6);
    geometry->set_attribute(1, colors, 6);

    return geometry;
}

Geometry *create_pyramid()
{
    vec3 positions[] = {
        {-0.55f, -0.55f, 0.0f},
        {-0.55f, 0.55f, 0.0f},
        {0.55f, 0.55f, 0.0f},
        {0.55f, -0.55f, 0.0f},
        {0.0f, 0.0f, 0.55f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.5f, 0.0f, 0.6f, 1.0f},
        {0.2f, 0.5f, 1.0f, 1.0f}};

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 18;
    GLuint indices[size] = {0, 1, 3, 3, 2, 1, 4, 0, 1, 4, 1, 2, 4, 2, 3, 4, 0, 3};
    geometry->set_indices(indices, size);

    geometry->set_vertices(0, positions, 5);
    geometry->set_attribute(1, colors, 5);

    return geometry;
}

Geometry *create_triangle()
{
    vec3 positions[] = {
        {0.0f, 0.0f, 0.0f},
        {0.5f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f}};

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
    vec2 texture_coordinates[] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f}};

    vec3 positions[] = {
        {-0.55, -0.55, 0.0f},
        {-0.55, 0.55, 0.0f},
        {0.55, 0.55, 0.0f},
        {0.55, -0.55, 0.0f}};

    vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.2f, 0.5f, 1.0f, 1.0f}};

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 6;
    GLuint indices[size] = {0, 1, 3, 2, 1, 3};
    geometry->set_indices(indices, size);

    geometry->set_vertices(0, positions, 4);
    geometry->set_attribute(1, colors, 4);
    geometry->set_attribute(7, texture_coordinates, 4);

    return geometry;
}