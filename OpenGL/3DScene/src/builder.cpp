#include "builder.h"

Geometry *create_axes()
{
    Geometry *geometry = new Geometry();

    glm::vec3 positions[] = {
        {0.0f, 0.0f, 0.0f},
        {0.7f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.7f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.7f}};

    glm::vec4 colors[] = {
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
    glm::vec3 positions[] = {
        {-0.55f, -0.55f, 0.0f},
        {-0.55f, 0.55f, 0.0f},
        {0.55f, 0.55f, 0.0f},
        {0.55f, -0.55f, 0.0f},
        {0.0f, 0.0f, 0.55f}};

    glm::vec4 colors[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {0.5f, 0.0f, 0.6f, 1.0f},
        {0.2f, 0.5f, 1.0f, 1.0f}};

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 18;
    GLuint indices[size] = {0, 1, 3,
                            3, 2, 1,
                            4, 0, 1,
                            4, 1, 2,
                            4, 2, 3,
                            4, 0, 3};
    geometry->set_indices(indices, size);

    geometry->set_vertices(0, positions, 5);
    geometry->set_attribute(1, colors, 5);

    return geometry;
}

Geometry *create_triangle()
{
    glm::vec3 positions[] = {
        {0.0f, 0.0f, 0.0f},
        {0.5f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f}};

    glm::vec4 colors[] = {
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
    glm::vec2 texture_coordinates[] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f}};

    glm::vec3 positions[] = {
        {-0.55, -0.55, 0.0f},
        {-0.55, 0.55, 0.0f},
        {0.55, 0.55, 0.0f},
        {0.55, -0.55, 0.0f}};

    glm::vec4 colors[] = {
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

Geometry *create_cube()
{
    glm::vec3 positions[] = {
        {0.0f, 0.0f, 0.0f},
        {0.5f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {0.0f, 0.0f, 0.5f},
        {0.5f, 0.0f, 0.5f},
        {0.0f, 0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f}};

    glm::vec4 colors[] = {
        {0.75f, 0.95f, 0.52f, 1.0f},
        {0.65f, 0.85f, 0.62f, 1.0f},
        {0.55f, 0.75f, 0.92f, 1.0f},
        {0.45f, 0.65f, 0.02f, 1.0f},
        {0.35f, 0.55f, 0.22f, 1.0f},
        {0.25f, 0.45f, 0.32f, 1.0f},
        {0.15f, 0.35f, 0.52f, 1.0f},
        {0.05f, 0.25f, 0.72f, 1.0f},
    };

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 36;
    GLuint indices[size] = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 5,
        0, 4, 5,
        0, 4, 6,
        0, 2, 6,
        4, 5, 7,
        7, 4, 6,
        2, 3, 7,
        6, 7, 2,
        1, 3, 7,
        1, 5, 7};
    geometry->set_indices(indices, size);

    geometry->set_vertices(0, positions, 8);
    geometry->set_attribute(1, colors, 8);

    return geometry;
}