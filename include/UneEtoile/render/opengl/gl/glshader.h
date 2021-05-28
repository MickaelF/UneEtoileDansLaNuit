#pragma once

#include <UneEtoile/render/opengl/commonglshader.h>

class GLShader : public CommonGLShader
{
public:
    GLShader(const char* name, std::string_view vertex, std::string_view fragment);
};