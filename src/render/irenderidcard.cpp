#include <UneEtoile/render/irenderidcard.h>
#include <UneEtoile/render/texturefactory.h>

IRenderIDCard::~IRenderIDCard() {}

void IRenderIDCard::addTexture(std::filesystem::path path)
{
    auto* tex = TextureFactory::instance().generateTexture(path);
    if (tex) m_textures.push_back(tex);
}

void IRenderIDCard::removeTexture(std::filesystem::path path) {}
