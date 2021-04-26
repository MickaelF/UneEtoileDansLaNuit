#pragma once
#include <pttk/log.h>

#include "basicinputs.h"
#include "input/iactionlistener.h"

class AbstractRenderer;
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

    int show();
    void quit() { m_keepRunning = false; }

private:
    void handleWindowEvent(SDL_Event& event);

    SDL_Window* m_window {nullptr};
    bool m_keepRunning {true};
    AbstractRenderer* m_renderer {nullptr};
};
