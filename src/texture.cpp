#include "texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "log.h"
#include "texturefactory.h"
#include <stdexcept>

Texture::Texture(const std::filesystem::path& path)
{
    lDebug << "Loading texture file " << path.c_str();
    auto data = stbi_load(path.string().c_str(), &m_width, &m_height, &m_nbChannels, 0);
    if (!data)
        throw std::runtime_error("Could not load file " + path.string());
    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::increaseUseNumber()
{
    m_numberUse++;
}

void Texture::decreaseUseNumber()
{
    if (--m_numberUse == 0)
        TextureFactory::instance().unloadTexture(this);
}
