#include <UneEtoile/render/texturefactory.h>
#define STB_IMAGE_IMPLEMENTATION
#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/render/opengl/opengltexture.h>
#include <pttk/log.h>
#include <stb/stb_image.h>
TextureFactory& TextureFactory::instance()
{
    static TextureFactory factory;
    return factory;
}

Texture* TextureFactory::generateTexture(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) return nullptr;
    auto it =
        std::find_if(m_generatedTexture.cbegin(), m_generatedTexture.cend(),
                     [&](const auto& pair) { return pair.first == path; });
    if (it != m_generatedTexture.cend()) return it->second;
    Texture* tex {nullptr};
    int width, height, channels;
    lDebug << "Loading texture file " << path.c_str();
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels,
                          STBI_rgb_alpha);
    if (!data) throw std::runtime_error("Could not load file " + path.string());
    switch (AbstractRenderer::instance()->type())
    {
        case AbstractRenderer::Type::OpenGl:
            tex = new OpenGlTexture(width, height, channels);
            break;
        default: break;
    }
    tex->load(data);
    stbi_image_free(data);

    m_generatedTexture.push_back(std::make_pair(path, tex));
    return tex;
}

void TextureFactory::unloadTexture(Texture* tex)
{
    m_generatedTexture.erase(
        std::find_if(m_generatedTexture.begin(), m_generatedTexture.end(),
                     [&tex](const auto& pair) { return pair.second == tex; }));
    delete tex;
}
