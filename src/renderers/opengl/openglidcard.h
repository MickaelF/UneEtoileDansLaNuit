#pragma once

#include "renderers/irenderidcard.h"

class OpenGlIDCard : public IRenderIDCard
{
public:
    explicit OpenGlIDCard(unsigned int vao, unsigned int vbo, unsigned int ebo);
    virtual ~OpenGlIDCard();
    void clear() override;

    const unsigned int vao;
    const unsigned int vbo;
    const unsigned int ebo;
};