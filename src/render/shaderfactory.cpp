#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/render/renderermacros.h>
#include <UneEtoile/render/shaderfactory.h>

#include <filesystem>
#include <tuple>
#if defined(OPENGL_FOUND)
    #include <UneEtoile/render/opengl/gl/glshader.h>
#elif defined(OPENGLES2_FOUND)
    #include <UneEtoile/render/opengl/gles/glesshader.h>
#endif

#include <pttk/file/plaintextfile.h>
#include <pttk/log.h>

namespace
{
std::optional<std::string> getShaderFileContent(
    const std::filesystem::path& path)
{
    PlainTextFile reader;
    auto source = reader.wholeFile(path.string());
    if (!source.has_value())
    {
        lError << "Could not find shader file " << path.string();
    }
    return source;
}

std::tuple<std::string, std::string> getGLShaders(
    const std::filesystem::path& path)
{
    return std::make_tuple(
        getShaderFileContent(std::filesystem::path(path).concat(".vert"))
            .value(),
        getShaderFileContent(std::filesystem::path(path).concat(".frag"))
            .value());
}
} // namespace

AbstractShader* ShaderFactory::shader(std::string_view name)
{
    switch (AbstractRenderer::instance()->type())
    {
        case AbstractRenderer::Type::OpenGL:
#if defined(OPENGL_FOUND)
            return glShader(name);
#elif defined(OPENGLES2_FOUND)
            return glesShader(name);
#endif
        default: return nullptr;
    }
}

#if defined(OPENGL_FOUND)
AbstractShader* ShaderFactory::glShader(std::string_view name)
{
    constexpr const char* path {"/shaders/gl/"};
    auto completePath {
        std::filesystem::current_path().concat(path).concat(name)};
    auto files {getGLShaders(completePath)};
    return new GLShader(name.data(), std::get<0>(files), std::get<1>(files));
}

#elif defined(OPENGLES2_FOUND)
AbstractShader* ShaderFactory::glesShader(std::string_view name)
{
    constexpr const char* path {"/shaders/gles/"};

    std::filesystem::path completePath =
        std::filesystem::current_path().string() + path + name;
    auto files {getGLShaders(completePath)};
    return new GLESShader(name.data(), std::get<0>(files), std::get<1>(files));
}
#endif
