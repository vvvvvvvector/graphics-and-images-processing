#include "texture2d.h"

Texture2D::Texture2D(const char *filepath, unsigned char slot)
{
    stbi_set_flip_vertically_on_load(1);

    local_buffer = stbi_load(filepath, &width, &height, &bits_per_pixel, 4);

    glGenTextures(1, &handle);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (local_buffer)
        stbi_image_free(local_buffer);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &handle);
}

void Texture2D::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
