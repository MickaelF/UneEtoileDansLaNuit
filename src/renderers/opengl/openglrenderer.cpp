#include "openglrenderer.h"

#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include <stdexcept>

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl.h"
#include "openglidcard.h"

namespace
{
constexpr const char* glsl_version {"#version 460"};
} // namespace

void OpenGlRenderer::init(SDL_Window* window)
{
    m_window = window;
    m_contextGL = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_contextGL);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    initImGui();
}

void OpenGlRenderer::render(GameObject* root) {}

uint32_t OpenGlRenderer::windowFlags()
{
    return SDL_WINDOW_OPENGL;
}

void OpenGlRenderer::clean()
{
    SDL_GL_DeleteContext(m_contextGL);
    ImGui_ImplOpenGL3_Shutdown();
    AbstractRenderer::clean();
}

void OpenGlRenderer::renderBegin()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::renderEnd()
{
    renderImGui();
    SDL_GL_SwapWindow(m_window);
}

void OpenGlRenderer::initImGui()
{
    AbstractRenderer::initImGui();
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_contextGL);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void OpenGlRenderer::beginImGuiRender()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void OpenGlRenderer::endImGuiRender()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
