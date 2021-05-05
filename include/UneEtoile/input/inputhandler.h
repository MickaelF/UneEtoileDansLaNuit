#pragma once
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_keycode.h>

#include <chrono>
#include <glm/vec2.hpp>
#include <optional>
#include <vector>

#include <UneEtoile/input/inputtype.h>

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

    void handleGamepadInput(
        const std::vector<GamepadInput>& inputs,
        std::chrono::time_point<std::chrono::steady_clock> now);
    void handleKeyboardInput(
        const std::vector<KeyboardInput>& inputs,
        std::chrono::time_point<std::chrono::steady_clock> now);
    void handleMouseInput(
        const std::vector<MouseInput>& inputs,
        std::chrono::time_point<std::chrono::steady_clock> now);

    void startRecording();

private:
    InputHandler() = default;
    std::vector<AbstractControlScheme*> m_controlScheme;
    AbstractControlScheme* m_currentScheme;
    static glm::ivec2 m_mousePosition;
    InputRecorder* m_recorder {nullptr};
};