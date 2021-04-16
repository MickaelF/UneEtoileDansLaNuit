#include "mainwindow.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <pttk/log.h>

#include "input/inputhandler.h"
#include "mesh.h"

MainWindow::MainWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("Failed to create SDL window");

    m_window = SDL_CreateWindow("LearnOpenGL", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 1600, 900,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!m_window) throw std::runtime_error("Failed to create SDL window");

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_renderer) throw std::runtime_error("Failed to create renderer.");

    // Create a OpenGL context on SDL2
    SDL_GLContext gl_context = SDL_GL_CreateContext(m_window);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
}

MainWindow::~MainWindow()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

int MainWindow::show()
{
    bool isRunning = true;
    auto inputHandler = InputHandler::instance();
    SDL_Event e;
    std::vector<GamepadInput> gamepadInputs;
    std::vector<KeyboardInput> keyboardInputs;
    std::vector<MouseInput> mouseInputs;
    while (isRunning)
    {
        gamepadInputs.clear();
        keyboardInputs.clear();
        mouseInputs.clear();
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_WINDOWEVENT: handleWindowEvent(e); break;
                case SDL_QUIT: isRunning = false; return 0;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    keyboardInputs.push_back(
                        {e.key.keysym.scancode, e.key.state});
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
            inputHandler.handleGamepadInput(gamepadInputs);
        if (!keyboardInputs.empty())
            inputHandler.handleKeyboardInput(keyboardInputs);
        if (!mouseInputs.empty()) inputHandler.handleMouseInput(mouseInputs);
        // Clear screen
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }
    return 0;
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
