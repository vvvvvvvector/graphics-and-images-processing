#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

#include <iostream>

#include "stb_image.h"

class Texture2D
{
private:
    GLuint handle;
    std::string filepath;
    unsigned char *local_buffer;
    int width, height, bits_per_pixel;

public:
    Texture2D();
    ~Texture2D();

    void bind(int texture_unit);
    void unbind();

    void load_texture_from_file(const std::string &filepath);
};

#endif // TEXTURE2D_H