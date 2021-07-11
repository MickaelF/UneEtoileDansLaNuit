#include <UneEtoile/appinfo.h>
#include <UneEtoile/imgui/widget/gameobjectwidget.h>
#include <UneEtoile/scene/gameobject.h>
#include <UneEtoile/scene/mesh.h>
#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

GameObjectWidget* GameObjectWidget::m_widget {nullptr};
void GameObjectWidget::changeGameObject(GameObject* obj)
{
    delete m_widget;
    if (obj)
        m_widget = new GameObjectWidget(obj);
    else
        m_widget = nullptr;
}

GameObjectWidget::GameObjectWidget(GameObject* obj)
    : IImGuiUserInterface(obj->name().c_str()),
      m_obj(obj)
{
}

void GameObjectWidget::render()
{
    static AppInfo* appInfo {AppInfo::instance()};
    if (!m_widget) return;
    ImGui::SetNextWindowPos(ImVec2(appInfo->windowWidth() - 200.0f, 200.0f));
    ImGui::SetNextWindowSize(ImVec2(200.0f, 200.0f));
    if (ImGui::Begin(name))
    {
        ImGui::Text("Transform");
        ImGui::DragFloat3("Position",
                          glm::value_ptr(m_obj->transform().m_position), 0.01f);
        ImGui::DragFloat3("Rotation",
                          glm::value_ptr(m_obj->transform().m_rotation), 0.01f);
        ImGui::DragFloat3("Scale", glm::value_ptr(m_obj->transform().m_scale),
                          0.01f);

        ImGui::Separator();
        Mesh* mesh {dynamic_cast<Mesh*>(m_obj)};
        if (mesh)
        {
            ImGui::NewLine();
            ImGui::Text("Shaders");
            for (auto* shader : mesh->shaders()) shader->imguiRender();
        }
    }
    ImGui::End();
}