#pragma once
#include <variant>
#include <vector>

class Action;

enum class InputType
{
    MouseButton,
    Keyboard,
    GamepadAxis,
    GamepadButton
};

/*
    Type de Binding :
        - button : value entre -1 et 1 (bouton ou axe unique (x ou y du joystick
   gauche ou droit uniquement))
        - 2D Vector : valeur entre (-1, -1) et (1, 1). Peut être un joystick
   (deux axes) ou un composé (quatres boutons)

*/
class Binding
{
public:
    // virtual const std::vector<std::pair<InputType, int>> inputs() = 0;
};

class ButtonBinding : public Binding
{
public:
    explicit ButtonBinding(InputType type, int key);
    // const std::vector<std::pair<InputType, int>> inputs() override;
    void setValue(unsigned int state);

private:
    InputType m_type;
    int m_key;
    bool m_started;
    bool m_held;
    bool m_released;
};

class AxisBinding : public Binding
{
public:
    explicit AxisBinding(InputType axis, int key);
    explicit AxisBinding(InputType negative, int negativeKey,
                         InputType positive, int positiveKey);

private:
    struct Axis
    {
        InputType axis;
        int key;
    };
    struct TwoButtonAxis
    {
        InputType negative;
        InputType positive;
        int negativeKey;
        int positiveKey;
    };
    std::variant<Axis, TwoButtonAxis> m_axis;
};
