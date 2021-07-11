#include <UneEtoile/imgui/iimguiuserinterface.h>
#include <UneEtoile/imgui/imguihandler.h>
#include <UneEtoile/window/mainwindow.h>
#include <pttk/log.h>

#include "imgui.h"

namespace
{
std::vector<IImGuiUserInterface*> toAdd;
std::vector<IImGuiUserInterface*> toRemove;
} // namespace

ImGuiHandler& ImGuiHandler::instance()
{
    static ImGuiHandler instance;
    return instance;
}

void ImGuiHandler::renderAll()
{
    renderMainMenu();
    if (m_displayMessageWidget) renderMessageWidget();
    for (auto& ui : m_ui) ui->render();
    if (!toAdd.empty())
    {
        m_ui.insert(m_ui.end(), toAdd.begin(), toAdd.end());
        toAdd.clear();
    }
    if (!toRemove.empty())
    {
        m_ui.erase(std::remove_if(m_ui.begin(), m_ui.end(),
                                  [&](IImGuiUserInterface* ui)
                                  {
                                      for (auto* r : toRemove)
                                          if (ui == r) return true;
                                      return false;
                                  }),
                   m_ui.end());
        toRemove.clear();
    }
}

void ImGuiHandler::addUI(IImGuiUserInterface* ptr)
{
    toAdd.push_back(ptr);
}

void ImGuiHandler::removeUI(IImGuiUserInterface* ptr)
{
    toRemove.push_back(ptr);
}

void ImGuiHandler::displayMessageWidget(MessageType type,
                                        const std::string& message)
{
    m_messagesVector.push_back(std::make_pair(message, type));
    if (!m_displayMessageWidget) m_displayMessageWidget = true;
}

void ImGuiHandler::renderMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Quit")) { m_mainWindow->quit(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            for (auto& ui : m_ui)
                if (ImGui::MenuItem(ui->name, nullptr, ui->visible))
                {
                    ui->visible = !ui->visible;
                }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug"))
        {
            if (ImGui::MenuItem("Display error message"))
            {
                displayMessageWidget(
                    MessageType::Error,
                    "This is a generic error message only to test "
                    "the error display widget.");
            }
            if (ImGui::MenuItem("Display warning message"))
            {
                displayMessageWidget(
                    MessageType::Warning,
                    "This is a generic warning message only to test "
                    "the error display widget.");
            }
            if (ImGui::MenuItem("Display info message"))
            {
                displayMessageWidget(
                    MessageType::Info,
                    "This is a generic info message only to test "
                    "the error display widget.");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void ImGuiHandler::renderMessageWidget()
{
    std::vector<
        std::vector<std::pair<std::string, MessageType>>::const_iterator>
        toRemove;
    for (auto it = m_messagesVector.cbegin(); it != m_messagesVector.cend();
         ++it)
    {
        // Always center this window when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing,
                                ImVec2(0.5f, 0.5f));

        if (ImGui::Begin(messageType(it->second), nullptr,
                         ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("%s", it->first.c_str());
            ImGui::Separator();

            if (ImGui::Button("OK", ImVec2(120, 0))) { toRemove.push_back(it); }
            ImGui::SetItemDefaultFocus();
            ImGui::End();
        }
    }
    for (const auto& it : toRemove) { m_messagesVector.erase(it); }
    m_displayMessageWidget = !m_messagesVector.empty();
}

constexpr const char* ImGuiHandler::messageType(MessageType type) const
{
    switch (type)
    {
        case MessageType::Error: return "Error";
        case MessageType::Warning: return "Warning";
        case MessageType::Info: return "Info";
        default: return "Unknown";
    }
}
