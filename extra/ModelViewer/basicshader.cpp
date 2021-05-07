#include "basicshader.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

namespace
{
}

BasicShader::BasicShader() : OpenGlShader("BasicShader"), m_widget(this) {}

BasicShader::~BasicShader() {}

BasicShaderWidget::BasicShaderWidget(BasicShader* ptr)
    : IImGuiUserInterface(ptr->name),
      m_shader(ptr)
{
}

BasicShaderWidget::~BasicShaderWidget() {}

void BasicShaderWidget::render()
{
    if (ImGui::Begin(name))
    {
        ImGui::ColorEdit4("Color", glm::value_ptr(m_shader->m_color));
        ImGui::End();
    }
}