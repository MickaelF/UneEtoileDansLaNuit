#include <UneEtoile/render/opengl/opengltexture.h>
#include <UneEtoile/render/renderermacros.h>
#include <pttk/log.h>

#ifdef OPENGL_FOUND
#include <glad/glad.h>

OpenGlTexture::OpenGlTexture(int width, int height, int nbChannels)
    : Texture(width, height, nbChannels)
{
}

OpenGlTexture::~OpenGlTexture() {}

void OpenGlTexture::load(unsigned char* data)
{
    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGlTexture::unload() {}

#else
OpenGlTexture::OpenGlTexture(int width, int height, int nbChannels)  : Texture(width, height, nbChannels){
    lFatal << "OpenGL renderer is not included on this platform and cannot be used!";
}
OpenGlTexture::~OpenGlTexture(){}

void OpenGlTexture::load(unsigned char* data) {}
void OpenGlTexture::unload(){}
#endif