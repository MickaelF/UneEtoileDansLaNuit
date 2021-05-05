#include <UneEtoile/render/basicshader.h>

#include <stdexcept>
#include <string_view>

#include <UneEtoile/render/shaderutil.h>

namespace
{
constexpr std::string_view shaderFileName {"basicshader"};
}

BasicShader::BasicShader()
{
    auto vertexId = ShaderUtil::generateVertexShader(shaderFileName);
    if (!vertexId.has_value())
        throw std::runtime_error(
            "Could not compile vertex shader for basicshader");
    auto fragId = ShaderUtil::generateFragmentShader(shaderFileName);
    if (!fragId.has_value())
        throw std::runtime_error(
            "Could not compile fragment shader for basicshader");

    auto program = ShaderUtil::generateProgram(*vertexId, *fragId);
    ShaderUtil::deleteShader(*vertexId);
    ShaderUtil::deleteShader(*fragId);
    if (!program.has_value())
        throw std::runtime_error(
            "Could not create the program for shader basicshader");
    m_programId = *program;
}