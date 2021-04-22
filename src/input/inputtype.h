#pragma once
#include <pttk/stringtools.h>

enum class InputType
{
    MouseButton,
    Keyboard,
    GamepadAxis,
    GamepadButton
};

struct GamepadInput
{
    int32_t padId;
    bool isAxis = false; // if true, divide value by 2^15
    uint8_t btnId;
    int16_t value;

    inline std::string str() const
    {
        return std::to_string(padId) + ',' +
               std::to_string(static_cast<int>(isAxis)) + ',' +
               std::to_string(btnId) + ',' + std::to_string(value);
    }

    inline static GamepadInput fromStr(const std::string& str)
    {
        GamepadInput input;
        auto values = strTls::split(str, ',');
        input.padId = std::stoi(values[0]);
        input.isAxis = static_cast<bool>(std::stoi(values[1]));
        input.btnId = std::stoi(values[2]);
        input.value = std::stoi(values[3]);
        return input;
    }
};

struct KeyboardInput
{
    int32_t key;
    uint8_t value;

    inline std::string str() const
    {
        return std::to_string(key) + ',' + std::to_string(value);
    }

    inline static KeyboardInput fromStr(const std::string& str)
    {
        KeyboardInput input;
        auto values = strTls::split(str, ',');
        input.key = std::stoi(values[0]);
        input.value = std::stoi(values[1]);
        return input;
    }
};

struct MouseInput
{
    uint8_t button;
    uint8_t value;
    bool wheel = false;
    int32_t x = 0;
    int32_t y = 0;

    inline std::string str() const
    {
        return std::to_string(button) + ',' + std::to_string(value) + ',' +
               std::to_string(static_cast<int>(wheel)) + ',' +
               std::to_string(x) + ',' + std::to_string(y);
    }

    inline static MouseInput fromStr(const std::string& str)
    {
        MouseInput input;
        auto values = strTls::split(str, ',');
        input.button = std::stoi(values[0]);
        input.value = std::stoi(values[1]);
        input.wheel = static_cast<bool>(std::stoi(values[2]));
        input.x = std::stoi(values[3]);
        input.y = std::stoi(values[4]);
        return input;
    }
};