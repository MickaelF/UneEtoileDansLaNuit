#include "inputrecorder.h"

#include <pttk/pttkpath.h>
#include <pttk/stringtools.h>

#include <fstream>

#include "appinfo.h"

namespace
{
std::string cstrInputStr(std::string inputType, std::string structText,
                         std::chrono::milliseconds duration)
{
    return inputType + ',' + structText + ',' +
           std::to_string(duration.count()) + '\n';
}
} // namespace

InputRecorder::InputRecorder() {}
InputRecorder::~InputRecorder()
{
    if (m_isRunning) stop();
}

void InputRecorder::handleGamepadInput(
    const std::vector<GamepadInput>& inputs,
    std::chrono::time_point<std::chrono::steady_clock> now)
{
    if (m_isPaused) return;
    auto diff =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& input : inputs)
        m_recordQueue.push(cstrInputStr("gamepad", input.str(), diff));
}

void InputRecorder::handleKeyboardInput(
    const std::vector<KeyboardInput>& inputs,
    std::chrono::time_point<std::chrono::steady_clock> now)
{
    if (m_isPaused) return;
    auto diff =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& input : inputs)
        m_recordQueue.push(cstrInputStr("keyboard", input.str(), diff));
}

void InputRecorder::handleMouseInput(
    const std::vector<MouseInput>& inputs,
    std::chrono::time_point<std::chrono::steady_clock> now)
{
    if (m_isPaused) return;
    auto diff =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start);
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& input : inputs)
        m_recordQueue.push(cstrInputStr("mouse", input.str(), diff));
}

void InputRecorder::start(const std::string& path)
{
    AppInfo& info = AppInfo::instance();
    m_path = (path.empty()) ? pttkPath::getDocumentFolderPath(
                                  info.appName(), info.companyName())
                            : path;
    m_isRunning = true;
    m_start = std::chrono::steady_clock::now();
    m_recorderThread = std::thread {&InputRecorder::flush, this};
}

void InputRecorder::stop()
{
    m_isRunning = false;
    m_recorderThread.join();
}

void InputRecorder::flush()
{
    using namespace std::chrono_literals;
    std::string fileName {m_path.string() + '/' +
                          strTls::currentDateTimeToString("%Y-%m-%d %H_%M_%S") +
                          ".irec"};
    std::ofstream outStream(fileName, std::ios::binary);
    while (m_isRunning)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_condition.wait_for(lock, 3s,
                                 [&] { return !m_recordQueue.empty(); }))
        {
            while (!m_recordQueue.empty())
            {
                outStream << m_recordQueue.front();
                m_recordQueue.pop();
            }
            outStream << std::flush;
        }
    }
}