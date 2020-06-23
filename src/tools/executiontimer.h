#pragma once
#include <chrono>
#include <iostream>
#include <string>

class ExecutionTimer
{
public:
    ExecutionTimer() = delete;
    ExecutionTimer(const ExecutionTimer&) = delete;
    ExecutionTimer(ExecutionTimer&&) = delete;
    ExecutionTimer& operator=(const ExecutionTimer&) = delete;
    ExecutionTimer(std::string&& name) : m_name(name), m_start(std::chrono::system_clock::now()) {}

    ~ExecutionTimer()
    {
        auto end = std::chrono::system_clock::now();
        auto duration = end - m_start;
        // TODO(mfle) Output this in a file rather than in the console.
        std::cout << m_name << ": "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
                  << "ms\n";
    }

private:
    const std::string m_name;
    std::chrono::time_point<std::chrono::system_clock> m_start;
};
