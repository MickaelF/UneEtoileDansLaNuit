#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include <string>
#include <variant>
#include <vector>

class IActionListener;
class Binding;
class AbstractControlScheme;

enum class ActionType
{
    Binary,
    Range,
    TwoDimension
};
class Action
{
public:
    explicit Action(AbstractControlScheme& scheme, const char* name);
    virtual ~Action() {}

    void addListener(IActionListener* listener);
    void removeListener(IActionListener* listener);
    bool hasListener(IActionListener* listener) const;
    bool isActive() const { return m_active; }
    void setActive(bool state);

    virtual ActionType type() const = 0;
    const char* name;
    void notify(Binding* binding);

protected:
    virtual void p_notify(Binding* binding) = 0;
    std::vector<IActionListener*> m_listeners;

private:
    bool m_active {true};
    AbstractControlScheme& m_scheme;
};

class BinaryAction : public Action
{
public:
    explicit BinaryAction(AbstractControlScheme& scheme, const char* name);
    ActionType type() const override { return ActionType::Binary; }
    
    bool on() const { return m_on; }
protected:
    void p_notify(Binding* binding) override;
private:
    bool m_on;
};

class RangeAction : public Action
{
public:
    explicit RangeAction(AbstractControlScheme& scheme, const char* name);
    ActionType type() const override { return ActionType::Range; }
   ;
    float value() const { return m_value; }

protected:
     void p_notify(Binding* binding) override;

private:
    bool m_fullRange = true;
    float m_value = 0.0f;
};

class Vector2Action : public Action
{
public:
    explicit Vector2Action(AbstractControlScheme& scheme, const char* name);
    ActionType type() const override { return ActionType::TwoDimension; }
    
    const glm::vec2& value() const { return m_value; }
protected:
    void p_notify(Binding* binding) override;
private:
    glm::vec2 m_value;
};
