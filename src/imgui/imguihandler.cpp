#include "imguihandler.h"

#include <pttk/log.h>

#include "iimguiuserinterface.h"
#include "imgui.h"
#include "mainwindow.h"

ImGuiHandler& ImGuiHandler::instance()
{
    static ImGuiHandler instance;
    return instance;
}

void ImGuiHandler::renderAll()
{
    renderMainMenu();
    for (auto& ui : m_ui) ui->render();
}

void ImGuiHandler::addUI(IImGuiUserInterface* ptr)
{
    m_ui.push_back(ptr);
}

void ImGuiHandler::removeUI(IImGuiUserInterface* ptr)
{
    m_ui.erase(std::find(m_ui.cbegin(), m_ui.cend(), ptr));
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
        ImGui::EndMainMenuBar();
    }
}

void ImGuiHandler::displayErrorWidget()
{
    if (!ImGui::Begin("Error"))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    ImGui::Text("%s", m_errorText.c_str());
    ImGui::Button("Ok");
    ImGui::End();
}
