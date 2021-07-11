#include "basicshader.h"

#include <UneEtoile/render/abstractshader.h>

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

namespace
{
constexpr std::string_view shaderName {"BasicShader"};
}

BasicShader::BasicShader()
    : AbstractShaderHandler(AbstractShader::getShader(shaderName))
{
}

BasicShader::~BasicShader() {}

void BasicShader::updateUniforms()
{
    static int colorId = m_shader->retrieveUniformId("color");
    if (m_colorChanged)
    {
        m_shader->updateUniform4f(colorId, m_color);
        m_colorChanged = false;
    }
    AbstractShaderHandler::updateUniforms();
}

void BasicShader::imguiRender()
{
    ImGui::Text("Basic Shader");
    m_colorChanged =
        m_colorChanged | ImGui::ColorEdit4("Color", glm::value_ptr(m_color));
    ImGui::NewLine();
}