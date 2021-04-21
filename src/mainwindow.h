#pragma once
#include <pttk/log.h>

#include "basicinputs.h"
#include "input/iactionlistener.h"

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
    void initOpenGl();
    void initImGui();
    void renderImGui();

    SDL_Window* m_window {nullptr};
    void* m_contextGL {nullptr};
    bool m_keepRunning {true};
};
