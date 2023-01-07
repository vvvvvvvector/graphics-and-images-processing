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
    Texture2D(const char *filepath, unsigned char slot);
    ~Texture2D();

    void bind(unsigned int slot);
    void unbind();
};

#endif // TEXTURE2D_H