#include <UneEtoile/appinfo.h>
#include <UneEtoile/imgui/imguihandler.h>
#include <UneEtoile/imgui/widget/appinfowidget.h>

#include "imgui.h"

AppInfoWidget::AppInfoWidget() : IImGuiUserInterface("App info") {}

void AppInfoWidget::render()
{
    static AppInfo& info = AppInfo::instance();
    if (m_currentRenderer == -1) m_currentRenderer = info.rendererIndex();
    if (!visible) return;
    if (ImGui::Begin(name, &visible))
    {
        if (ImGui::BeginTable(name, 2))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Application Name:");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", info.appName().c_str());

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Company Name:");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", info.companyName().c_str());

            const char* items[] = {"OpenGl", "DirectX", "Vulkan"};
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Renderer:");
            ImGui::TableSetColumnIndex(1);
            if (m_modifying)
                ImGui::Combo("", &m_currentRenderer, items,
                             IM_ARRAYSIZE(items));
            else
                ImGui::Text("%s", items[m_currentRenderer]);
            ImGui::TableNextRow();
            if (!m_modifying)
            {
                ImGui::TableSetColumnIndex(0);
                ImGui::TableSetColumnIndex(1);
                if (ImGui::Button("Change")) m_modifying = true;
            }
            else
            {
                ImGui::TableSetColumnIndex(0);
                if (ImGui::Button("Save")) save();
                ImGui::TableSetColumnIndex(1);
                if (ImGui::Button("Cancel"))
                {
                    m_modifying = false;
                    m_currentRenderer = info.rendererIndex();
                }
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}

bool AppInfoWidget::hasChanges() const
{
    if (m_currentRenderer != AppInfo::instance().rendererIndex()) return true;
    return false;
}

bool AppInfoWidget::needRestart() const
{
    if (m_currentRenderer != AppInfo::instance().rendererIndex()) return true;
    return false;
}

void AppInfoWidget::save()
{
    static AppInfo& info = AppInfo::instance();
    m_modifying = false;
    if (!hasChanges()) return;
    bool displayNeedRestart = needRestart();
    info.setRendererIndex(m_currentRenderer);
    if (!info.save())
    {
        ImGuiHandler::instance().displayMessageWidget(
            ImGuiHandler::MessageType::Error,
            "An error occured while saving the app info file.");
    }
    else if (displayNeedRestart)
    {
        ImGuiHandler::instance().displayMessageWidget(
            ImGuiHandler::MessageType::Info,
            "Changes made will be applied at next restart.");
    }
}