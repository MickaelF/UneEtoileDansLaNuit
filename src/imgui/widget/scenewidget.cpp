#include <UneEtoile/appinfo.h>
#include <UneEtoile/imgui/widget/gameobjectwidget.h>
#include <UneEtoile/imgui/widget/scenewidget.h>
#include <UneEtoile/scene/iscene.h>

#include "imgui.h"

void SceneWidget::treeNode(GameObject* go)
{
    GameObject* oldGO {m_selectedObj};
    bool selectedStyle = m_selectedObj == go;
    if (selectedStyle)
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.7f, 1.0f));
    if (go->children().empty())
    {
        if (ImGui::Selectable(go->name().c_str())) m_selectedObj = go;
    }
    else
    {
        if (ImGui::TreeNodeEx(go->name().c_str(),
                              ImGuiTreeNodeFlags_OpenOnArrow))
        {
            for (auto child : go->children()) treeNode(child);
            ImGui::TreePop();
        }
        if (ImGui::IsItemClicked()) m_selectedObj = go;
    }
    if (selectedStyle) ImGui::PopStyleColor();
    if (oldGO != m_selectedObj)
        GameObjectWidget::changeGameObject(m_selectedObj);
}

void SceneWidget::render()
{
    static AppInfo* appInfo {AppInfo::instance()};
    ImGui::SetNextWindowPos(ImVec2(appInfo->windowWidth() - 200.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(200.0f, 200.0f));
    bool open {true};
    if (ImGui::Begin(name, &open,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoResize))
    {
        for (auto& child : m_scene.m_root.children()) { treeNode(child); }
    }
    ImGui::End();
}