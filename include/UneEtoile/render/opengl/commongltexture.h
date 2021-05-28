#pragma once
#include <UneEtoile/render/abstracttexture.h>

class CommonGLTexture : public AbstractTexture
{
public:
    explicit CommonGLTexture(int width, int height, int nbChannels);
    virtual ~CommonGLTexture();

    void load(unsigned char* data) override;
    void unload() override;

    unsigned int texId() const { return m_texId; }

private:
    unsigned int m_texId;
};