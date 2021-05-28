#pragma once
#include<UneEtoile/render/renderermacros.h>

#ifdef OPENGL_FOUND
#include <UneEtoile/render/opengl/commonglrenderer.h>

class GLRenderer : public CommonGLRenderer
{
public:
    void init(SDL_Window* window) override;
   
protected:
    const char* glslVersion() const override { return "#version 330 core";}
};
#endif