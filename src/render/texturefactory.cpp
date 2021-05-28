#include <UneEtoile/render/texturefactory.h>
#define STB_IMAGE_IMPLEMENTATION
#include <UneEtoile/render/abstractrenderer.h>
#include<UneEtoile/render/renderermacros.h>
#if defined(OPENGL_FOUND)
#include <UneEtoile/render/opengl/gl/gltexture.h>
#elif defined(OPENGLES2_FOUND)
#include <UneEtoile/render/opengl/gles/glestexture.h>
#endif

#include <pttk/log.h>
#include <stb/stb_image.h>
TextureFactory& TextureFactory::instance()
{
    static TextureFactory factory;
    return factory;
}

AbstractTexture* TextureFactory::generateTexture(
    const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) return nullptr;
    auto it =
        std::find_if(m_generatedTexture.cbegin(), m_generatedTexture.cend(),
                     [&](const auto& pair) { return pair.first == path; });
    if (it != m_generatedTexture.cend()) return it->second;
    AbstractTexture* tex {nullptr};
    int width, height, channels;
    lDebug << "Loading texture file " << path.c_str();
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels,
                          STBI_rgb_alpha);
    if (!data) throw std::runtime_error("Could not load file " + path.string());
    switch (AbstractRenderer::instance()->type())
    {
        case AbstractRenderer::Type::OpenGL:
#if defined(OPENGL_FOUND)
            tex = new GLTexture(width, height, channels);
#elif defined(OPENGLES2_FOUND)
            tex = new GLESTexture(width, height, channels);
#endif
            break;
        default: break;
    }
    tex->load(data);
    stbi_image_free(data);

    m_generatedTexture.push_back(std::make_pair(path, tex));
    return tex;
}

void TextureFactory::unloadTexture(AbstractTexture* tex)
{
    m_generatedTexture.erase(
        std::find_if(m_generatedTexture.begin(), m_generatedTexture.end(),
                     [&tex](const auto& pair) { return pair.second == tex; }));
    delete tex;
}
