#pragma once
#include <glm/glm.hpp>

enum class InputType
{
    MouseButton,
    Keyboard,
    GamepadAxis,
    GamepadButton
};

class Input
{
public:
    explicit Input(int key) : m_key(key) {}
    int key() const { return m_key; }
    virtual InputType type() const = 0;

protected:
    const int m_key;
};

class ButtonInput : public Input
{
public:
    ButtonInput(int key) : Input(key) {}

    void setValue(bool value)
    {
        if (value)
        {
            if (m_held) return;
            if (m_started)
            {
                m_started = false;
                m_held = true;
            }
            else
            {
                m_started = true;
                if (m_released) m_released = false;
            }
        }
        else
        {
            if (m_started || m_held)
            {
                m_started = false;
                m_held = false;
                m_released = true;
            }
            else if (m_released)
            {
                m_released = false;
            }
        }
    }

    bool started() const { return m_started; }
    bool held() const { return m_held; }
    bool released() const { return m_released; }

protected:
    bool m_started;
    bool m_held;
    bool m_released;
};

class AxisInput : public Input
{
public:
    explicit AxisInput(int key) : Input(key) {}
    InputType type() const override { return InputType::GamepadAxis; }
    void setValue(float value);

private:
    float m_value;
};

class KeyboardInput : public ButtonInput
{
public:
    KeyboardInput(int key) : ButtonInput(key) {}

    InputType type() const override { return InputType::Keyboard; }
};

class MouseInput : public ButtonInput
{
public:
    MouseInput(int key) : ButtonInput(key) {}

    InputType type() const override { return InputType::MouseButton; }
    const glm::vec2i position() const { return m_position; }
    void setPosition(const glm::vec2i& pos)
    {
        if (m_position != pos) m_position = pos;
    }

private:
    glm::vec2i m_position;
};