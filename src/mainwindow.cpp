#include "mainwindow.h"

#include <SDL2/SDL.h>
#include <pttk/log.h>

#include "appinfo.h"
#include "imgui/imguihandler.h"
#include "input/inputhandler.h"
#include "iscene.h"
#include "renderers/abstractrenderer.h"

namespace
{
constexpr const char* glsl_version {"#version 460"};
} // namespace

MainWindow::MainWindow() : m_renderer(AbstractRenderer::instance())
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
        throw std::runtime_error("Failed to create SDL window");

    m_window =
        SDL_CreateWindow(AppInfo::instance().appName().c_str(),
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600,
                         900, SDL_WINDOW_SHOWN | m_renderer->windowFlags());
    if (!m_window) throw std::runtime_error("Failed to create SDL window");

    m_renderer->init(m_window);
    ImGuiHandler::instance().setMainWindow(this);
}

MainWindow::~MainWindow()
{
    m_renderer->clean();
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void MainWindow::inputHandling()
{
    auto inputHandler = InputHandler::instance();
    SDL_Event e;
    std::vector<GamepadInput> gamepadInputs;
    std::vector<KeyboardInput> keyboardInputs;
    std::vector<MouseInput> mouseInputs;
    std::chrono::time_point<std::chrono::steady_clock> now =
        std::chrono::steady_clock::now();
    while (SDL_PollEvent(&e))
    {
        m_renderer->processEvents(e);
        switch (e.type)
        {
            case SDL_WINDOWEVENT: handleWindowEvent(e); break;
            case SDL_QUIT: m_keepRunning = false; return;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                keyboardInputs.push_back({e.key.keysym.scancode, e.key.state});
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                gamepadInputs.push_back(
                    {e.jaxis.which, true, e.jaxis.axis, e.jaxis.value});
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouseInputs.push_back({e.button.button, e.button.state});
                break;
            case SDL_MOUSEWHEEL:
                mouseInputs.push_back({0, 0, true, e.wheel.x, e.wheel.y});
                break;
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                InputHandler::setMousePosition(x, y);
            }
            break;
            case SDL_JOYAXISMOTION:
                gamepadInputs.push_back(
                    {e.jaxis.which, true, e.jaxis.axis, e.jaxis.value});
                break;
            case SDL_JOYDEVICEADDED: break;
            case SDL_JOYDEVICEREMOVED: break;
        }
    }
    if (!gamepadInputs.empty())
        inputHandler.handleGamepadInput(gamepadInputs, now);
    if (!keyboardInputs.empty())
        inputHandler.handleKeyboardInput(keyboardInputs, now);
    if (!mouseInputs.empty()) inputHandler.handleMouseInput(mouseInputs, now);
}

void MainWindow::render()
{
    m_renderer->renderBegin();
    if (m_currentScene) m_renderer->render(m_currentScene->root());
    m_renderer->renderEnd();
}

void MainWindow::handleWindowEvent(SDL_Event& event)
{
    switch (event.window.event)
    {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("Window %d shown", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("Window %d hidden", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("Window %d exposed", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("Window %d moved to %d,%d", event.window.windowID,
                    event.window.data1, event.window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("Window %d resized to %dx%d", event.window.windowID,
                    event.window.data1, event.window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("Window %d size changed to %dx%d", event.window.windowID,
                    event.window.data1, event.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("Window %d minimized", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("Window %d maximized", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("Window %d restored", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("Mouse entered window %d", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("Mouse left window %d", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("Window %d gained keyboard focus", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("Window %d lost keyboard focus", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("Window %d closed", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("Window %d is offered a focus", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("Window %d has a special hit test", event.window.windowID);
            break;
        default:
            SDL_Log("Window %d got unknown event %d", event.window.windowID,
                    event.window.event);
            break;
    }
}