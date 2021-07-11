#pragma once

#include <cstdint>

class GameObject;
struct SDL_Window;
union SDL_Event;
class AbstractMeshHandler;

class AbstractRenderer
{
public:
    enum Type
    {
        OpenGL,
        Vulkan,
        DirectX
    };
    AbstractRenderer();
    virtual ~AbstractRenderer();
    static AbstractRenderer* instance();
    static void selectRendererType(Type type);

    virtual Type type() const = 0;
    virtual void init(SDL_Window* window) = 0;
    virtual uint32_t windowFlags() = 0;
    virtual void render(GameObject* root) = 0;
    virtual void clean();
    virtual void renderBegin() = 0;
    virtual void renderEnd() = 0;
    void processEvents(SDL_Event& event);

    virtual AbstractMeshHandler* meshHandler() const = 0;

protected:
    void renderImGui();
    virtual void initImGui();
    virtual void beginImGuiRender() = 0;
    virtual void endImGuiRender() = 0;

    SDL_Window* m_window {nullptr};

private:
    static AbstractRenderer* m_instance;
};