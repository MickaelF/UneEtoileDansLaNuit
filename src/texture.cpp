#include "texture.h"
#include "gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "log.h"
#include <stdexcept>

Texture::Texture(const std::filesystem::path& path)
{
    lDebug << "Loading texture file " << path.c_str();
    auto data = stbi_load(path.c_str(), &m_width, &m_height, m_nbChannels, 0);
    if (!data)
        throw std::runtime_error("Could not load file " + path.string());
    j
    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_textId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}