#include "texturefactory.h"

#include "texture.h"

TextureFactory& TextureFactory::instance()
{
    static TextureFactory factory;
    return factory;
}

Texture* TextureFactory::generateTexture(const std::filesystem::path& path)
{
    if (m_generatedTexture.contains(path))
        return m_generatedTexture[path].get();

    Texture* tex = new Texture {path};
    m_generatedTexture.emplace(std::make_pair(path, std::move(tex)));
    return tex;
}

void TextureFactory::unloadTexture(Texture* tex)
{
    m_generatedTexture.erase(std::find_if(
        m_generatedTexture.begin(), m_generatedTexture.end(),
        [&tex](const auto& pair) { return pair.second.get() == tex; }));
}
