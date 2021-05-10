#pragma once
#include <UneEtoile/input/inputenum.h>
#include <UneEtoile/input/inputtype.h>

#include <glm/glm.hpp>
#include <string>
#include <variant>
#include <vector>

class Action;

class Binding
{
public:
    Binding(const char* name) : name {name}, id {s_id++} {}
    virtual const std::vector<std::pair<InputType, int>> inputs() const = 0;

    virtual void setValue(InputType type, int key, float value) = 0;
    virtual void setValue(InputType type, int key, int value) = 0;

    void resetUsedController();
    void addUsedController(InputEnum type, int32_t gamepadId = 0);

    const char* name;
    const int id;
    void addAction(Action* action) { m_actions.push_back(action); }
    const InputData& usedControllers() const { return m_usedControllers; }

private:
    static int s_id;
    std::vector<Action*> m_actions;
    InputData m_usedControllers;
};

class BinaryBinding : public Binding
{
public:
    explicit BinaryBinding(InputType type, int key, const char* name = {});
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
    explicit RangeBinding(InputType axis, int key, const char* name = {});
    explicit RangeBinding(InputType negative, int negativeKey,
                          InputType positive, int positiveKey,
                          const char* name = {});

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
                   InputType verticalType, int verticalKey,
                   const char* name = {});
    Vector2Binding(InputType leftType, int leftKey, InputType topType,
                   int topKey, InputType rightType, int rightKey,
                   InputType bottomType, int bottomKey, const char* name = {});

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