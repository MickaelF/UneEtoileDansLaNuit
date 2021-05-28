#include <UneEtoile/render/opengl/gles/glestexture.h>
#ifdef OPENGLES2_FOUND
GLESTexture::GLESTexture(int width, int height, int nbChannels)
    : CommonGLTexture(width, height, nbChannels)
{
}
#endif