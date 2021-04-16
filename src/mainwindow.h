#pragma once
#include <pttk/log.h>

#include "basicinputs.h"
#include "input/iactionlistener.h"

struct SDL_Window;
struct SDL_Renderer;
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

private:
    void handleWindowEvent(SDL_Event& event);

    SDL_Window* m_window {nullptr};
    SDL_Renderer* m_renderer {nullptr};
};
