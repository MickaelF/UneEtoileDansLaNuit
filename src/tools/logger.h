#pragma once
#include <fstream>
#include <queue>
#include <string>
#include <string_view>

class Logger
{
public:
    ~Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;

    static void append(std::string_view str);
    static void close();

private:
    static Logger& get();
    Logger();
    void flush();

    std::queue<std::string> m_logQueue;
    std::ofstream m_fileStream;
    bool m_isRunning {true};
};
