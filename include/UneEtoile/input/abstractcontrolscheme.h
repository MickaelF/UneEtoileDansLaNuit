#pragma once
#include <optional>
#include <vector>

class AbstractActionMap;
struct GamepadInput;
struct KeyboardInput;
struct MouseInput;

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

    void setGamepadId(int32_t id);
    const std::optional<int32_t>& gamepadId() const { return m_gamepadId; }

    void handleGamepadInput(const std::vector<GamepadInput>& inputs);
    void handleKeyboardInput(const std::vector<KeyboardInput>& inputs);
    void handleMouseInput(const std::vector<MouseInput>& inputs);

protected:
    std::vector<AbstractActionMap*> m_actionMaps;

private:
    std::optional<int32_t> m_gamepadId {std::nullopt};
};