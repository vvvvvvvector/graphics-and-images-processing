#include "builder.h"

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

    Geometry *geometry = new Geometry();

    geometry->mode = GL_TRIANGLES;

    const int size = 6;
    GLuint indices[size] = {0, 1, 3, 2, 1, 3};
    geometry->set_indices(indices, size);

    geometry->set_vertices((int)Attributes::position, positions, 4);

    geometry->set_attribute((int)Attributes::texture, texture_coordinates, 4);

    return geometry;
}