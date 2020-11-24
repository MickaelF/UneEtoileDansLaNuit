#pragma once
#include <glm/glm.hpp>
#include <string>
#include <variant>
#include <vector>

#include "binding.h"

class IActionListener;

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
    explicit Action(const std::string& name, int id);
    ~Action();

    void notify(Binding& binding);

    void addListener(IActionListener* listener);
    void removeListener(IActionListener* listener);
    bool hasListener(IActionListener* listener) const;
    bool isActive() const { return m_active; }
    void activate() { m_active = true; }
    void deactivate() { m_active = false; }
    const std::vector<Binding>& bindings() const { return m_bindings; }

private:
    ActionContext context(bool started, bool ended) const;
    std::vector<IActionListener*> m_listeners;
    std::vector<Binding> m_bindings;
    std::variant<float, glm::vec2> m_value;
    bool m_inUse {false};
    const std::string m_name;
    const int m_id;
    bool m_active {true};
};