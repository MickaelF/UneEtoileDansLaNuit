#include "basicshader.h"

#include <UneEtoile/render/abstractshader.h>

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

namespace
{
constexpr std::string_view shaderName {"BasicShader"};
}

BasicShader::BasicShader()
    : m_widget(this),
      m_shader(AbstractShader::getShader(shaderName))
{
    m_colorId = m_shader->retrieveUniformId("color");
}

BasicShader::~BasicShader() {}

void BasicShader::updateUniforms() const
{
    if (m_imguiUpdate && m_colorId >= 0)
        m_shader->updateUniform4f(m_colorId, m_color);
}

void BasicShader::activate()
{
    m_shader->activate();
}

BasicShaderWidget::BasicShaderWidget(BasicShader* ptr)
    : IImGuiUserInterface(shaderName.data()),
      m_shader(ptr)
{
}

BasicShaderWidget::~BasicShaderWidget() {}

void BasicShaderWidget::render()
{
    if (ImGui::Begin(name))
    {
        m_shader->m_imguiUpdate =
            m_shader->m_imguiUpdate |
            ImGui::ColorEdit4("Color", glm::value_ptr(m_shader->m_color));
    }
    ImGui::End();
}