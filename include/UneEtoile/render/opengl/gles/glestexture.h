#pragma once
#include<UneEtoile/render/renderermacros.h>

#ifdef OPENGLES2_FOUND
#include <UneEtoile/render/opengl/commongltexture.h>

class GLESTexture : public CommonGLTexture
{
public:
    GLESTexture(int width, int height, int nbChannels);
};
#endif