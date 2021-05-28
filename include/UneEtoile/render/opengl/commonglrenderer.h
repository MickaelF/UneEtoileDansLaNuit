#pragma once

#include <UneEtoile/imgui/iimguiuserinterface.h>
class CommonGLRenderer;

class GLRendererImgui : public IImGuiUserInterface
{
public:
    GLRendererImgui(CommonGLRenderer* renderer);
    void render() override;

private:
    enum class RenderingMode
    {
        Point,
        Line,
        Triangle
    };

    enum class CullingMode
    {
        Back,
        Front,
        BackAndFront
    };

    enum class WindingMode
    {
        Clockwise,
        CounterClockwise
    };
    int renderingMode() const;
    int cullingMode() const;
    int windingMode() const;
    CommonGLRenderer* m_renderer {nullptr};
    bool m_culling {false};
    int m_rendererMode {static_cast<int>(RenderingMode::Triangle)};
    int m_cullingMode {static_cast<int>(CullingMode::Back)};
    int m_windingMode {static_cast<int>(WindingMode::CounterClockwise)};
};

#include <UneEtoile/render/abstractrenderer.h>

class CommonGLRenderer : public AbstractRenderer
{
public:
    CommonGLRenderer();
    virtual ~CommonGLRenderer();
    Type type() const override { return Type::OpenGL; }

    void render(GameObject* root) override;
    uint32_t windowFlags() override;
    void clean() override;
    void renderBegin() override;
    void renderEnd() override;
    IRenderIDCard* load(Mesh& mesh) override;
    void unload(IRenderIDCard* card) override;

protected:
    virtual const char* glslVersion() const = 0;
    void initImGui() override;
    void beginImGuiRender() override;
    void endImGuiRender() override;
    void* m_contextGL {nullptr};

private:
    int m_renderingMode;

    friend GLRendererImgui;
    GLRendererImgui m_imgui;
};
