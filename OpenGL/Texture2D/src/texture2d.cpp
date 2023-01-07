#include "texture2d.h"

Texture2D::Texture2D()
{
    glGenTextures(1, &handle);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &handle);
}

void Texture2D::bind(int texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::load_texture_from_file(const std::string &filepath)
{
    stbi_set_flip_vertically_on_load(1);

    local_buffer = stbi_load(filepath.c_str(), &width, &height, &bits_per_pixel, 4);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    bind(0);    
    unbind();

    if (local_buffer)
        stbi_image_free(local_buffer);
}
