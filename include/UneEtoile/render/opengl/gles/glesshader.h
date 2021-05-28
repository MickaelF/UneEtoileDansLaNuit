#pragma once
#include<UneEtoile/render/renderermacros.h>

#ifdef OPENGLES2_FOUND
#include <UneEtoile/render/opengl/commonglshader.h>

class GLESShader : public CommonGLShader
{
public:
    GLESShader(const char* name, std::string_view vertex, std::string_view fragment);
};
#endif