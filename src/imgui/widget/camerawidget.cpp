#include <UneEtoile/imgui/widget/camerawidget.h>
#include <UneEtoile/scene/camera.h>

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

CameraWidget::CameraWidget(Camera* obj)
    : IImGuiUserInterface("Camera"),
      m_ptr(obj)
{
}

void CameraWidget::render()
{
    if (ImGui::Begin(name))
    {
        ImGui::InputFloat3("Position", glm::value_ptr(m_ptr->m_position));
        ImGui::InputFloat3("Front", glm::value_ptr(m_ptr->m_front));
        ImGui::InputFloat3("Up", glm::value_ptr(m_ptr->m_up));
    }
    ImGui::End();
}