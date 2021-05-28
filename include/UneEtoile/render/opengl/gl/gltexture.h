#pragma once
#include<UneEtoile/render/renderermacros.h>

#ifdef OPENGL_FOUND
#include <UneEtoile/render/opengl/commongltexture.h>

class GLTexture : public CommonGLTexture
{
public:
    GLTexture(int width, int height, int nbChannels);
};
#endif