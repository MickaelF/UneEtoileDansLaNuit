#include <SDL2/SDL_video.h>
#include <UneEtoile/render/opengl/openglidcard.h>
#include <UneEtoile/render/opengl/openglrenderer.h>
#include <UneEtoile/scene/mesh.h>

#include <stdexcept>

#include "glad/glad.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

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

IRenderIDCard* OpenGlRenderer::load(Mesh& mesh)
{
    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto& vertices = mesh.vertices();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    auto& indices = mesh.indices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texcoords));

    glBindVertexArray(0);
    return new OpenGlIDCard(vao, vbo, ebo);
}

void OpenGlRenderer::unload(IRenderIDCard* card)
{
    OpenGlIDCard* oglCard = static_cast<OpenGlIDCard*>(card);
    glDeleteVertexArrays(1, &oglCard->vao);
    glDeleteBuffers(1, &oglCard->vbo);
    glDeleteBuffers(1, &oglCard->ebo);
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

OpenGlRenderer::~OpenGlRenderer() {}
