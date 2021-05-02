#pragma once
#include "renderers/texture.h"

class OpenGlTexture : public Texture
{
public:
    explicit OpenGlTexture(int width, int height, int nbChannels);
    virtual ~OpenGlTexture();

    void load(unsigned char* data) override;
    void unload() override;

    unsigned int texId() const { return m_texId; }

private:
    unsigned int m_texId;
};