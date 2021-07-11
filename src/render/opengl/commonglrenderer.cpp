#include <UneEtoile/render/opengl/commonglrenderer.h>
#include <UneEtoile/render/renderermacros.h>
#include <pttk/log.h>

#if defined(OPENGL_FOUND) || defined(OPENGLES2_FOUND)
    #include <SDL2/SDL_video.h>
    #include <UneEtoile/render/opengl/commonglidcard.h>
    #include <UneEtoile/render/opengl/commonglshader.h>
    #include <UneEtoile/render/opengl/commonglmeshhandler.h>
    #include <UneEtoile/scene/mesh.h>

    #include <stdexcept>

    #include "glad/glad.h"
    #include "imgui_impl_opengl3.h"
    #include "imgui_impl_sdl.h"

CommonGLRenderer::CommonGLRenderer()
    : m_renderingMode(GL_TRIANGLES),
      m_imgui(this)
{
}

void CommonGLRenderer::render(GameObject* root)
{
    if (!root) return;
    if (root->renderCard())
    {
        CommonGLIDCard* card = static_cast<CommonGLIDCard*>(root->renderCard());
        glBindVertexArray(card->vao);
        auto model {root->modelMatrix()};
        AbstractShader::currentShader->updateUniformMat4f(AbstractShader::currentShader->retrieveUniformId("modelMatrix"), root->modelMatrix());
        glDrawElements(m_renderingMode, card->nbIndices, GL_UNSIGNED_INT, 0);
    }
    for (auto& child : root->children()) render(child);

    glBindVertexArray(0);
}

AbstractMeshHandler* CommonGLRenderer::meshHandler() const
{
    static CommonGLMeshHandler handler;
    return &handler;
}

uint32_t CommonGLRenderer::windowFlags()
{
    return SDL_WINDOW_OPENGL;
}

void CommonGLRenderer::clean()
{
    SDL_GL_DeleteContext(m_contextGL);
    ImGui_ImplOpenGL3_Shutdown();
    AbstractRenderer::clean();
}

void CommonGLRenderer::renderBegin()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void CommonGLRenderer::renderEnd()
{
    renderImGui();
    SDL_GL_SwapWindow(m_window);
}

void CommonGLRenderer::initImGui()
{
    AbstractRenderer::initImGui();
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_contextGL);
    ImGui_ImplOpenGL3_Init(glslVersion());
}

void CommonGLRenderer::beginImGuiRender()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void CommonGLRenderer::endImGuiRender()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

CommonGLRenderer::~CommonGLRenderer() {}

GLRendererImgui::GLRendererImgui(CommonGLRenderer* renderer)
    : IImGuiUserInterface("OpenGL"),
      m_renderer(renderer)
{
}
int GLRendererImgui::renderingMode() const
{
    switch (static_cast<RenderingMode>(m_rendererMode))
    {
        case RenderingMode::Point: return GL_POINTS;
        case RenderingMode::Line: return GL_LINES;
        case RenderingMode::Triangle: return GL_TRIANGLES;
    }
    return GL_TRIANGLES;
}

int GLRendererImgui::cullingMode() const
{
    switch (static_cast<CullingMode>(m_cullingMode))
    {
        case CullingMode::Front: return GL_FRONT;
        case CullingMode::Back: return GL_BACK;
        case CullingMode::BackAndFront: return GL_FRONT_AND_BACK;
    }
    return GL_BACK;
}

int GLRendererImgui::windingMode() const
{
    if (static_cast<WindingMode>(m_windingMode) == WindingMode::Clockwise)
        return GL_CW;
    else
        return GL_CCW;
}

void GLRendererImgui::render()
{
    constexpr const char* cullingModes[] {"Back", "Front", "BackAndFront"};
    constexpr const char* windingModes[] {"Clockwise", "CounterClockWise"};
    constexpr const char* renderingModes[] {"Point", "Line", "Triangle"};
    if (!visible) return;
    if (ImGui::Begin(name, &visible))
    {
        if (ImGui::Checkbox("Culling Faces:", &m_culling))
        {
            if (m_culling)
            {
                glEnable(GL_CULL_FACE);
                glCullFace(renderingMode());
            }
            else
            {
                glDisable(GL_CULL_FACE);
            }
        }
        if (m_culling && ImGui::Combo("Culling mode:", &m_cullingMode,
                                      cullingModes, IM_ARRAYSIZE(cullingModes)))
        { glCullFace(cullingMode()); }
        if (ImGui::Combo("Rendering mode:", &m_rendererMode, renderingModes,
                         IM_ARRAYSIZE(renderingModes)))
        { m_renderer->m_renderingMode = renderingMode(); }
        if (ImGui::Combo("Winding mode:", &m_windingMode, windingModes,
                         IM_ARRAYSIZE(windingModes)))
        { glFrontFace(windingMode()); }
    }
    ImGui::End();
}
#else
CommonGLRenderer::CommonGLRenderer()
{
    lFatal << "OpenGL renderer is not included on this platform and cannot be "
              "used!";
}
CommonGLRenderer::~CommonGLRenderer() {}

void CommonGLRenderer::render(GameObject* root) {}
uint32_t CommonGLRenderer::windowFlags()
{
    return 0;
}
void CommonGLRenderer::clean() {}
void CommonGLRenderer::renderBegin() {}
void CommonGLRenderer::renderEnd() {}
void CommonGLRenderer::initImGui() {}
void CommonGLRenderer::beginImGuiRender() {}
void CommonGLRenderer::endImGuiRender() {}
#endif