#pragma once

#include <cstdint>

class IRenderIDCard;
struct SDL_Window;
union SDL_Event;

// TODO Display an error message if the constructor is being called somewhere
// else than in the instance creator.
class AbstractRenderer
{
public:
    enum Type
    {
        OpenGl,
        Vulkan,
        DirectX
    };
    AbstractRenderer() = default;
    static AbstractRenderer* instance();
    static void selectRendererType(Type type);

    virtual Type type() const = 0;
    virtual void init(SDL_Window* window) = 0;
    virtual uint32_t windowFlags() = 0;
    virtual void render(IRenderIDCard* id) = 0;
    virtual void clean();
    virtual void renderBegin() = 0;
    virtual void renderEnd() = 0;
    void processEvents(SDL_Event& event);

protected:
    void renderImGui();
    virtual void initImGui();
    virtual void beginImGuiRender() = 0;
    virtual void endImGuiRender() = 0;

    SDL_Window* m_window {nullptr};

private:
    static AbstractRenderer* m_instance;
};