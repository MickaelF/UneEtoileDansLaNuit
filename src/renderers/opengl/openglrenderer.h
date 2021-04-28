#pragma once

#include "renderers/abstractrenderer.h"

class OpenGlRenderer : public AbstractRenderer
{
public:
    OpenGlRenderer() = default;
    virtual ~OpenGlRenderer();
    Type type() const override { return Type::OpenGl; }

    void init(SDL_Window* window) override;
    void render(GameObject* root) override;
    uint32_t windowFlags() override;
    void clean() override;
    void renderBegin() override;
    void renderEnd() override;
    IRenderIDCard* load(Mesh& mesh) override;
    void unload(IRenderIDCard* card) override;

protected:
    void initImGui() override;
    void beginImGuiRender() override;
    void endImGuiRender() override;

private:
    void* m_contextGL {nullptr};
};