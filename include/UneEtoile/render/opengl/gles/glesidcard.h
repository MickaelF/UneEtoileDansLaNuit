#pragma once
#include<UneEtoile/render/renderermacros.h>

#ifdef OPENGLES2_FOUND
#include <UneEtoile/render/opengl/commonglidcard.h>

class GLESIDCard : public CommonGLIDCard
{
public:
    GLESIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo,
               unsigned int nbIndices);
};
#endif