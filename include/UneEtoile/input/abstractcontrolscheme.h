#pragma once

#include <optional>
#include <vector>
#include <UneEtoile/input/inputenum.h>

class Action;
struct Input;

class AbstractControlScheme
{
public:
    AbstractControlScheme(const char* name);
    ~AbstractControlScheme();

    const char* name;

    bool isActive() const;
    void setActive(bool state);

    void setGamepadId(int32_t id);
    const std::optional<int32_t>& gamepadId() const { return m_gamepadId; }
    bool acceptInput(InputData input) const;

protected:
    InputEnum m_acceptedInputs = InputEnum::All;
    std::vector<Action*> m_actions;
    void loadBindings();

private:
    std::optional<int32_t> m_gamepadId {std::nullopt};
};
