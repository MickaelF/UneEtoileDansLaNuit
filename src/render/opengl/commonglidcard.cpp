#include <UneEtoile/render/abstractrenderer.h>
#include <UneEtoile/render/opengl/commonglidcard.h>
CommonGLIDCard::CommonGLIDCard(unsigned int vao, unsigned int vbo,
                               unsigned int ebo, unsigned int nbIndices)
    : vao {vao},
      vbo {vbo},
      ebo {ebo},
      nbIndices {nbIndices}
{
}

CommonGLIDCard::~CommonGLIDCard()
{
    clear();
}

void CommonGLIDCard::clear()
{
    AbstractRenderer::instance()->unload(this);
}