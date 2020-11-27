#pragma once
#include <glm/glm.hpp>
#include <string>
#include <variant>
#include <vector>

class IActionListener;
class Binding;

enum class ActionType
{
    Button,
    Axis,
    TwoDimension
};

struct ActionContext
{
    const std::variant<float, glm::vec2> value;
    const bool started;
    const bool performed;
    const bool ended;
    const int id;
};

class Action
{
public:
    explicit Action(const std::string& name);

    void notify(Binding& binding);

    void addListener(IActionListener* listener);
    void removeListener(IActionListener* listener);
    bool hasListener(IActionListener* listener) const;
    bool isActive() const { return m_active; }
    void setActive(bool state);
    std::vector<Binding*>& bindings() { return m_bindings; }

    void addBinding(Binding* binding);

private:
    ActionContext context(bool started, bool ended) const;
    std::vector<IActionListener*> m_listeners;
    std::vector<Binding*> m_bindings;
    std::variant<float, glm::vec2> m_value;
    bool m_inUse {false};
    const std::string m_name;
    const int m_id;
    bool m_active {true};
};