#pragma once
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_keycode.h>
#include <UneEtoile/imgui/widget/controlschemewidget.h>
#include <UneEtoile/input/inputtype.h>

#include <chrono>
#include <glm/vec2.hpp>
#include <optional>
#include <vector>

class AbstractControlScheme;
class InputRecorder;
struct SDL_Window;

class InputHandler
{
public:
    static InputHandler& instance();

    static glm::ivec2 mousePosition();
    static void setMousePosition(int x, int y);

    void addControlScheme(AbstractControlScheme* scheme);
    void removeControlScheme(AbstractControlScheme* scheme);

    void handleInputs(const std::vector<Input>& inputs,
                      std::chrono::time_point<std::chrono::steady_clock> now);

    void startRecording();

private:
    InputHandler() = default;
    std::vector<AbstractControlScheme*> m_controlScheme;
    AbstractControlScheme* m_currentScheme;
    static glm::ivec2 m_mousePosition;
    InputRecorder* m_recorder {nullptr};
    friend ControlSchemeWidget;
    ControlSchemeWidget m_controlSchemeWidget;
};