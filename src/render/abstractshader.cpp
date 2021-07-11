#include <UneEtoile/render/abstractshader.h>
#include <UneEtoile/render/shaderfactory.h>

AbstractShader* AbstractShader::currentShader {nullptr};

AbstractShader::AbstractShader(const char* name) : name(name) {}

AbstractShader::~AbstractShader() {}

AbstractShader* AbstractShader::getShader(std::string_view name)
{
    return ShaderFactory::shader(name);
}
