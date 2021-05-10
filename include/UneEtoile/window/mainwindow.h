#pragma once
#include <UneEtoile/scene/camera.h>
#include <pttk/log.h>

class AbstractRenderer;
class IScene;
struct SDL_Window;
union SDL_Event;

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();
    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

    bool running() const { return m_keepRunning; }
    void inputHandling();
    void render();
    void quit() { m_keepRunning = false; }

private:
    void handleWindowEvent(SDL_Event& event);

    SDL_Window* m_window {nullptr};
    bool m_keepRunning {true};
    AbstractRenderer* m_renderer {nullptr};
    IScene* m_currentScene {nullptr};
    Camera m_camera;
};
