#pragma once
#include <UneEtoile/input/inputenum.h>

#include <variant>

enum class InputType
{
    MouseButton,
    MouseWheel,
    Keyboard,
    GamepadAxis,
    GamepadButton
};

struct GamepadValue
{
    int32_t padId;
    int16_t value;
};

struct KeyboardValue
{
    uint8_t value;
};

struct MouseValue
{
    uint8_t value;
    int posX {};
    int posY {};
};

struct MouseWheelValue
{
    int wheelX {};
    int wheelY {};
};

struct Input
{
    InputType type;
    int key;
    std::variant<GamepadValue, KeyboardValue, MouseValue, MouseWheelValue>
        value;
};