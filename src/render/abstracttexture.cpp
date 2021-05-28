#include <UneEtoile/render/abstracttexture.h>

#include <UneEtoile/render/texturefactory.h>

AbstractTexture::AbstractTexture(int width, int height, int nbChannels)
    : width(width),
      height(height),
      nbChannels(nbChannels)
{
}

AbstractTexture::~AbstractTexture() {}

void AbstractTexture::increaseUseNumber()
{
    m_numberUse++;
}

void AbstractTexture::decreaseUseNumber()
{
    if (--m_numberUse == 0) TextureFactory::instance().unloadTexture(this);
}
