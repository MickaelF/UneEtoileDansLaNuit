#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include <string>
#include <variant>
#include <vector>

class IActionListener;
class Binding;

enum class ActionType
{
    Binary,
    Range,
    TwoDimension
};
class Action
{
public:
    explicit Action(const std::string& name);
    virtual ~Action() {}

    virtual void notify(Binding* binding) = 0;

    void addListener(IActionListener* listener);
    void removeListener(IActionListener* listener);
    bool hasListener(IActionListener* listener) const;
    bool isActive() const { return m_active; }
    void setActive(bool state);

    virtual ActionType type() const = 0;

protected:
    std::vector<IActionListener*> m_listeners;

private:
    const std::string m_name;
    const int m_id;
    bool m_active {true};
};

class BinaryAction : public Action
{
public:
    explicit BinaryAction(const std::string& name);
    ActionType type() const override { return ActionType::Binary; }
    void notify(Binding* binding) override;
    bool on() const { return m_on; }

private:
    bool m_on;
};

class RangeAction : public Action
{
public:
    explicit RangeAction(const std::string& name);
    ActionType type() const override { return ActionType::Range; }
    void notify(Binding* binding) override;
    float value() const { return m_value; }

private:
    bool m_fullRange = true;
    float m_value = 0.0f;
};

class Vector2Action : public Action
{
public:
    explicit Vector2Action(const std::string& name);
    ActionType type() const override { return ActionType::TwoDimension; }
    void notify(Binding* binding) override;
    const glm::vec2& value() const { return m_value; }

private:
    glm::vec2 m_value;
};
