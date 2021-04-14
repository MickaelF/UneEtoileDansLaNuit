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

class Binding
{
public:
    Binding(Action& action, const std::string& name)
        : m_action {action},
          m_name {name}
    {
        bindings.push_back(this);
    }
    virtual const std::vector<std::pair<InputType, int>> inputs() const = 0;

    virtual void setValue(InputType type, int key, float value) = 0;
    virtual void setValue(InputType type, int key, int value) = 0;

    const std::string& name() const;

    static std::vector<Binding*> bindings;

private:
    Action& m_action;
    const std::string m_name;
};

class BinaryBinding : public Binding
{
public:
    explicit BinaryBinding(InputType type, int key, Action& action,
                           const std::string& name = {});
    const std::vector<std::pair<InputType, int>> inputs() const override;
    void setValue(InputType type, int key, int value) override;
    void setValue(InputType type, int key, float value) override;

    bool pressed() const { return m_pressed; }

private:
    InputType m_type;
    int m_key;
    bool m_pressed;
};

class RangeBinding : public Binding
{
public:
    explicit RangeBinding(InputType axis, int key, Action& action,
                          const std::string& name = {});
    explicit RangeBinding(InputType negative, int negativeKey,
                          InputType positive, int positiveKey, Action& action,
                          const std::string& name = {});

    void setValue(InputType type, int key, int value) override;
    void setValue(InputType type, int key, float value) override;

    const std::vector<std::pair<InputType, int>> inputs() const override;

    float value() const;

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

class Vector2Binding : public Binding
{
public:
    Vector2Binding(InputType horizontalType, int horizontalKey,
                   InputType verticalType, int verticalKey, Action& action,
                   const std::string& name = {});
    Vector2Binding(InputType leftType, int leftKey, InputType topType,
                   int topKey, InputType rightType, int rightKey,
                   InputType bottomType, int bottomKey, Action& action,
                   const std::string& name = {});

    void setValue(InputType type, int key, int value) override;
    void setValue(InputType type, int key, float value) override;

    const std::vector<std::pair<InputType, int>> inputs() const override;

    glm::vec2 value() const;

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