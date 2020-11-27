#pragma once
#include <glm/glm.hpp>
#include <string>
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
    Binding(const std::string& name) : m_name {name} {}
    virtual const std::vector<std::pair<InputType, int>> inputs() const = 0;

    virtual void setValue(InputType type, int key, float value) = 0;
    virtual void setValue(InputType type, int key, int value) = 0;

    const std::string& name() const;

private:
    const std::string m_name;
};

class ButtonBinding : public Binding
{
public:
    explicit ButtonBinding(InputType type, int key,
                           const std::string& name = {});
    const std::vector<std::pair<InputType, int>> inputs() const override;
    void setValue(InputType type, int key, int value) override;
    void setValue(InputType type, int key, float value) override;

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
    explicit AxisBinding(InputType axis, int key, const std::string& name = {});
    explicit AxisBinding(InputType negative, int negativeKey,
                         InputType positive, int positiveKey,
                         const std::string& name = {});

    void setValue(InputType type, int key, int value) override;
    void setValue(InputType type, int key, float value) override;

    const std::vector<std::pair<InputType, int>> inputs() const override;

private:
    struct Axis
    {
        InputType type;
        int key;
        float value {};
    };

    struct TwoButtonAxis
    {
        InputType negative;
        int negativeKey;
        InputType positive;
        int positiveKey;
        int positiveValue {};
        int negativeValue {};
    };

    std::variant<Axis, TwoButtonAxis> m_axis;
};

class Vector2DBinding : public Binding
{
public:
    Vector2DBinding(InputType horizontalType, int horizontalKey,
                    InputType verticalType, int verticalKey,
                    const std::string& name = {});
    Vector2DBinding(InputType leftType, int leftKey, InputType topType,
                    int topKey, InputType rightType, int rightKey,
                    InputType bottomType, int bottomKey,
                    const std::string& name = {});

    void setValue(InputType type, int key, int value) override;
    void setValue(InputType type, int key, float value) override;

    const std::vector<std::pair<InputType, int>> inputs() const override;

private:
    struct TwoAxisVector
    {
        InputType horizontalType;
        int horizontalKey;
        InputType verticalType;
        int verticalKey;
        float horizontalValue {};
        float verticalValue {};
    };

    struct FourButtonVector
    {
        InputType leftType;
        int leftKey;
        InputType topType;
        int topKey;
        InputType rightType;
        int rightKey;
        InputType bottomType;
        int bottomKey {};
        int leftValue {};
        int topValue {};
        int rightValue {};
        int bottomValue {};
    };
    std::variant<TwoAxisVector, FourButtonVector> m_vector2D;
};