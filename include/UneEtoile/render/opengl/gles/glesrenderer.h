#pragma once
#include<UneEtoile/render/renderermacros.h>

#ifdef OPENGLES2_FOUND
#include <UneEtoile/render/opengl/commonglrenderer.h>

class GLESRenderer : public CommonGLRenderer
{
public:
    void init(SDL_Window* window) override;
protected:
    const char* glslVersion() const override { return "#version 300 es";}
};
#endif