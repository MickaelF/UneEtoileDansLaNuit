#pragma once
#include <optional>
#include <vector>

class AbstractControlScheme;
struct GLFWwindow;

class InputHandler
{
public:
    InputHandler() = default;
    static InputHandler& instance();

    void addControlScheme(AbstractControlScheme* scheme);
    void removeControlScheme(AbstractControlScheme* scheme);

    void run();
    void setWindow(GLFWwindow* window);

private:
    float getAxisValueFromGamepad(int key, std::optional<int> gamepadId);
    int getButtonValueFromGamepad(int key, std::optional<int> gamepadId);

    std::vector<AbstractControlScheme*> m_controlScheme;
    GLFWwindow* m_window {nullptr};
};