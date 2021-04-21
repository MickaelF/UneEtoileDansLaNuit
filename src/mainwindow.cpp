#include "mainwindow.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <pttk/log.h>

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui/imguihandler.h"
#include "input/inputhandler.h"
#include "mesh.h"

namespace
{
constexpr const char* glsl_version {"#version 460"};
} // namespace

MainWindow::MainWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
        throw std::runtime_error("Failed to create SDL window");

    m_window = SDL_CreateWindow("LearnOpenGL", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 1600, 900,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!m_window) throw std::runtime_error("Failed to create SDL window");

    // Create a OpenGL context on SDL2
    m_contextGL = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_contextGL);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    initOpenGl();
    initImGui();
}

MainWindow::~MainWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(m_contextGL);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void MainWindow::initOpenGl()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void MainWindow::renderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui::NewFrame();
    ImGuiHandler::instance().renderAll();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainWindow::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(m_window, m_contextGL);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGuiHandler::instance().setMainWindow(this);
}

int MainWindow::show()
{
    auto inputHandler = InputHandler::instance();
    SDL_Event e;
    std::vector<GamepadInput> gamepadInputs;
    std::vector<KeyboardInput> keyboardInputs;
    std::vector<MouseInput> mouseInputs;
    while (m_keepRunning)
    {
        gamepadInputs.clear();
        keyboardInputs.clear();
        mouseInputs.clear();
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
            switch (e.type)
            {
                case SDL_WINDOWEVENT: handleWindowEvent(e); break;
                case SDL_QUIT: m_keepRunning = false; return 0;
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

        glClear(GL_COLOR_BUFFER_BIT);
        renderImGui();
        SDL_GL_SwapWindow(m_window);
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