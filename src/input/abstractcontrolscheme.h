#pragma once
#include <optional>
#include <vector>
class AbstractActionMap;

class AbstractControlScheme
{
public:
    AbstractControlScheme();
    ~AbstractControlScheme();

    const std::vector<AbstractActionMap*>& actionsMaps() const
    {
        return m_actionMaps;
    }

    bool isActive() const;
    void setActive(bool state);

    void setGamepadId(int id);
    const std::optional<int>& gamepadId() const { return m_gamepadId; }

protected:
    std::vector<AbstractActionMap*> m_actionMaps;

private:
    std::optional<int> m_gamepadId {std::nullopt};
};