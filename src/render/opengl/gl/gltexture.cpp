#include <UneEtoile/render/opengl/gl/gltexture.h>
#ifdef OPENGL_FOUND
GLTexture::GLTexture(int width, int height, int nbChannels)
    : CommonGLTexture(width, height, nbChannels)
{
}
#endif