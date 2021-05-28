#include <UneEtoile/render/opengl/gl/glidcard.h>
#ifdef OPENGL_FOUND
GLIDCard::GLIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo,
                   unsigned int nbIndices)
    : CommonGLIDCard(vao, vbo, ebo, nbIndices)
{
}
#endif