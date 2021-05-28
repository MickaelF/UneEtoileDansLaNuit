#include <UneEtoile/render/opengl/gles/glesidcard.h>
#ifdef OPENGLES2_FOUND
GLESIDCard::GLESIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo,
                       unsigned int nbIndices)
    : CommonGLIDCard(vao, vbo, ebo, nbIndices)
{
}
#endif