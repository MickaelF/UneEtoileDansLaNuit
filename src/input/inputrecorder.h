#pragma once

#include <chrono>
#include <condition_variable>
#include <filesystem>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "inputtype.h"

class InputRecorder
{
    // TODO : Faire un widget ImGui timeline qui permet de se ballader dans les
    // inputs
public:
    InputRecorder();
    ~InputRecorder();

    void start(const std::string& path = std::string());
    void stop();
    void pause() { m_isPaused = true; }
    void unpause() { m_isPaused = false; }

    void handleGamepadInput(
        const std::vector<GamepadInput>& inputs,
        std::chrono::time_point<std::chrono::steady_clock> now);
    void handleKeyboardInput(
        const std::vector<KeyboardInput>& inputs,
        std::chrono::time_point<std::chrono::steady_clock> now);
    void handleMouseInput(
        const std::vector<MouseInput>& inputs,
        std::chrono::time_point<std::chrono::steady_clock> now);

private:
    void flush();

    std::queue<std::string> m_recordQueue;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::thread m_recorderThread;
    bool m_isRunning {false};
    bool m_isPaused {false};
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::filesystem::path m_path;
};
