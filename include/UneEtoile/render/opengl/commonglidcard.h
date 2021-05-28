#pragma once

#include <UneEtoile/render/irenderidcard.h>

class CommonGLIDCard : public IRenderIDCard
{
public:
    explicit CommonGLIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo,
                          unsigned int nbIndices);
    virtual ~CommonGLIDCard();
    void clear() override;

    const unsigned int vao;
    const unsigned int vbo;
    const unsigned int ebo;
    const unsigned int nbIndices;
};