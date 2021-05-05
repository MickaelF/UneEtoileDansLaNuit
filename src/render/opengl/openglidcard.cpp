#include <UneEtoile/render/opengl/openglidcard.h>

#include <UneEtoile/render/abstractrenderer.h>
OpenGlIDCard::OpenGlIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo)
    : vao {vao},
      vbo {vbo},
      ebo {ebo}
{
}
OpenGlIDCard::~OpenGlIDCard()
{
    clear();
}
void OpenGlIDCard::clear()
{
    AbstractRenderer::instance()->unload(this);
}