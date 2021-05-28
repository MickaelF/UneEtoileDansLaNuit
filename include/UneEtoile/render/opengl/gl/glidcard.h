#pragma once
#include<UneEtoile/render/renderermacros.h>
#ifdef OPENGL_FOUND
#include <UneEtoile/render/opengl/commonglidcard.h>

class GLIDCard : public CommonGLIDCard
{
public:
    GLIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo,
             unsigned int nbIndices);
};
#endif