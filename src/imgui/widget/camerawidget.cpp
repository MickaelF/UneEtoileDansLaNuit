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
        ImGui::Text("Transform");
        m_ptr->m_viewChanged =
            ImGui::DragFloat3("Position", glm::value_ptr(m_ptr->m_position),
                              0.1f) ||
            m_ptr->m_viewChanged;
        m_ptr->m_viewChanged =
            ImGui::DragFloat3("Front", glm::value_ptr(m_ptr->m_front), 0.1f) ||
            m_ptr->m_viewChanged;
        m_ptr->m_viewChanged =
            ImGui::DragFloat3("Up", glm::value_ptr(m_ptr->m_up), 0.1f) ||
            m_ptr->m_viewChanged;

        ImGui::Separator();
        ImGui::Text("Parameters");
        m_ptr->m_projectionChanged =
            ImGui::SliderFloat("FOV", &m_ptr->m_fov, 40.0f, 120.0f);
    }
    ImGui::End();
}