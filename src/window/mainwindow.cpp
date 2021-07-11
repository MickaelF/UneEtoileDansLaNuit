#include <SDL2/SDL.h>
#include <UneEtoile/appinfo.h>
#include <UneEtoile/imgui/imguihandler.h>
#include <UneEtoile/input/inputhandler.h>
#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/scene/camera.h>
#include <UneEtoile/scene/iscene.h>
#include <UneEtoile/window/mainwindow.h>
#include <pttk/log.h>

namespace
{
constexpr const char* glsl_version {"#version 460"};
} // namespace

MainWindow::MainWindow() : m_renderer(AbstractRenderer::instance())
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
        throw std::runtime_error("Failed to create SDL window");
    auto* appInfo {AppInfo::instance()};
    m_window = SDL_CreateWindow(appInfo->appName().c_str(),
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                appInfo->windowWidth(), appInfo->windowHeight(),
                                SDL_WINDOW_SHOWN | m_renderer->windowFlags());
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
    auto& inputHandler = InputHandler::instance();
    SDL_Event e;
    std::vector<Input> inputs;
    while (SDL_PollEvent(&e))
    {
        m_renderer->processEvents(e);
        switch (e.type)
        {
            case SDL_WINDOWEVENT: handleWindowEvent(e); break;
            case SDL_QUIT: m_keepRunning = false; return;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                Input input {InputType::Keyboard, e.key.keysym.scancode,
                             KeyboardValue {e.key.state}};
                inputs.push_back(input);
            }
            break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            {
                Input input {InputType::GamepadButton, e.jbutton.button,
                             GamepadValue {e.jbutton.which, e.jbutton.state}};
                inputs.push_back(input);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                Input input {
                    InputType::MouseButton, e.button.button,
                    MouseValue {e.button.state, e.button.x, e.button.y}};
                inputs.push_back(input);
            }
            break;
            case SDL_MOUSEWHEEL:
            {
                // TODO Handle differently.
                Input input {InputType::MouseWheel, 0,
                             MouseWheelValue {e.wheel.x, e.wheel.y}};
                inputs.push_back(input);
            }
            break;
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                auto oldMousePos = InputHandler::mousePosition();
                InputHandler::setMousePosition(x, y);
            }
            break;
            case SDL_JOYAXISMOTION:
            {
                Input input {InputType::GamepadAxis, e.jaxis.axis,
                             GamepadValue {e.jaxis.which, e.jaxis.value}};
                inputs.push_back(input);
            }
            break;
            case SDL_JOYDEVICEADDED: break;
            case SDL_JOYDEVICEREMOVED: break;
        }
    }
    if (!inputs.empty())
        inputHandler.handleInputs(inputs, std::chrono::steady_clock::now());
}

void MainWindow::render(IScene* m_currentScene)
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