#include "abstractrenderer.h"

#include <stdexcept>

#include "backends/imgui_impl_sdl.h"
#include "imgui/imguihandler.h"
#include "renderers/opengl/openglrenderer.h"

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
        case Type::OpenGl: m_instance = new OpenGlRenderer(); break;
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
