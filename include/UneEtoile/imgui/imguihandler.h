#pragma once
#include <string>
#include <vector>

class IImGuiUserInterface;
class MainWindow;
/*

    TODO:
        -  Ajouter un menu pour lancer la sauvegarde des inputs et la lecture
   des fichiers d'inputs
        - creer un widget pour les messages d'erreur, un pour les sauvegardes,
   un pour les noms de fichiers
*/
class ImGuiHandler
{
public:
    enum class MessageType
    {
        Info,
        Warning,
        Error
    };
    static ImGuiHandler& instance();

    void renderAll();

    void addUI(IImGuiUserInterface* ptr);
    void removeUI(IImGuiUserInterface* ptr);

    void setMainWindow(MainWindow* mainWindow) { m_mainWindow = mainWindow; }

    void displayMessageWidget(MessageType type, const std::string& message);

private:
    ImGuiHandler() = default;

    void renderMainMenu();
    void renderMessageWidget();

    constexpr const char* messageType(MessageType type) const;

    std::vector<IImGuiUserInterface*> m_ui;
    MainWindow* m_mainWindow {nullptr};

    bool m_displayMessageWidget {false};
    std::vector<std::pair<std::string, MessageType>> m_messagesVector;
};