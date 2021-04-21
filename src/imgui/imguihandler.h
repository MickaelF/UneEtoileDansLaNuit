#pragma once
#include <vector>

class IImGuiUserInterface;
class MainWindow;

class ImGuiHandler
{
public:
    static ImGuiHandler& instance();

    void renderAll();

    void addUI(IImGuiUserInterface* ptr);
    void removeUI(IImGuiUserInterface* ptr);

    void setMainWindow(MainWindow* mainWindow) { m_mainWindow = mainWindow; }

private:
    ImGuiHandler() = default;

    void renderMainMenu();

    std::vector<IImGuiUserInterface*> m_ui;
    MainWindow* m_mainWindow {nullptr};
};