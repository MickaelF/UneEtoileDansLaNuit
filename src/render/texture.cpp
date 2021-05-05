#include <UneEtoile/render/texture.h>

#include <UneEtoile/render/texturefactory.h>

Texture::Texture(int width, int height, int nbChannels)
    : width(width),
      height(height),
      nbChannels(nbChannels)
{
}

Texture::~Texture() {}

void Texture::increaseUseNumber()
{
    m_numberUse++;
}

void Texture::decreaseUseNumber()
{
    if (--m_numberUse == 0) TextureFactory::instance().unloadTexture(this);
}
