#pragma once
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_keycode.h>

#include <optional>
#include <vector>

class AbstractControlScheme;
struct SDL_Window;

struct GamepadInput
{
    SDL_JoystickID padId;
    bool isAxis = false; // if true, divide value by 2^15
    Uint8 btnId;
    Sint16 value;
};

struct KeyboardInput
{
    SDL_Keycode key;
    Uint8 value;
};

struct MouseInput
{
    Uint8 button;
    Uint8 value;
    bool wheel = false;
    Sint32 x = 0;
    Sint32 y = 0;
};

class InputHandler
{
public:
    InputHandler() = default;
    static InputHandler& instance();

    void addControlScheme(AbstractControlScheme* scheme);
    void removeControlScheme(AbstractControlScheme* scheme);

    void handleGamepadInput(const std::vector<GamepadInput>& inputs);
    void handleKeyboardInput(const std::vector<KeyboardInput>& inputs);
    void handleMouseInput(const std::vector<MouseInput>& inputs);

private:
    std::vector<AbstractControlScheme*> m_controlScheme;
};