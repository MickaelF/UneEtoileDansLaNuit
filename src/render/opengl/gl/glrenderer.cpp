#include <UneEtoile/render/opengl/gl/glrenderer.h>
#include <UneEtoile/render/renderermacros.h>
#ifdef OPENGL_FOUND
    #include <SDL2/SDL_video.h>
    #include <glad/glad.h>

    #include <stdexcept>

    #include "imgui_impl_sdl.h"
void GLRenderer::init(SDL_Window* window)
{
    m_window = window;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    m_contextGL = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_contextGL);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    initImGui();
}
#endif