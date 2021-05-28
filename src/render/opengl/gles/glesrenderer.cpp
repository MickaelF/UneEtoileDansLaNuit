#include <UneEtoile/render/opengl/gles/glesrenderer.h>
#include <UneEtoile/render/renderermacros.h>
#ifdef OPENGLES2_FOUND
    #include <SDL2/SDL_video.h>
    #include <glad/glad.h>

    #include <stdexcept>

    #include "imgui_impl_sdl.h"

void GLESRenderer::init(SDL_Window* window)
{
    m_window = window;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    m_contextGL = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_contextGL);

    // Load GL extensions using glad
    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    glViewport(0, 0, 1600, 900);
    initImGui();
}
#endif