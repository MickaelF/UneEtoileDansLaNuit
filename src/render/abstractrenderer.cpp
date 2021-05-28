#include <UneEtoile/imgui/imguihandler.h>
#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/render/renderermacros.h>
#if defined(OPENGL_FOUND)
#include <UneEtoile/render/opengl/gl/glrenderer.h>
#elif defined(OPENGLES2_FOUND)
#include <UneEtoile/render/opengl/gles/glesrenderer.h>
#endif

#include <stdexcept>

#include "imgui_impl_sdl.h"

AbstractRenderer* AbstractRenderer::m_instance {nullptr};

AbstractRenderer* AbstractRenderer::instance()
{
    if (m_instance) return m_instance;
    throw std::runtime_error(
        "Renderer needs to be instantiated before being used!");
}

AbstractRenderer::AbstractRenderer()
{
    if (m_instance)
        throw std::runtime_error("A second renderer cannot be instanciated!");
}

AbstractRenderer::~AbstractRenderer() {}

void AbstractRenderer::selectRendererType(Type type)
{
    if (m_instance)
        throw std::runtime_error(
            "Impossible to change renderer type at runtime! Change saved type "
            "and restart to change used renderer.");

    switch (type)
    {
        case Type::OpenGL: 
#if defined(OPENGL_FOUND)
        m_instance = new GLRenderer();
#elif defined(OPENGLES2_FOUND)
        m_instance = new GLESRenderer();
#endif
        break;
        case Type::DirectX:
        case Type::Vulkan: break;
    }
}

void AbstractRenderer::clean()
{
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void AbstractRenderer::processEvents(SDL_Event& event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void AbstractRenderer::renderImGui()
{
    beginImGuiRender();
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui::NewFrame();
    ImGuiHandler::instance().renderAll();
    ImGui::Render();
    endImGuiRender();
}

void AbstractRenderer::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
}
