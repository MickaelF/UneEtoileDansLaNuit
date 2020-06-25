#pragma once
#include <fstream>
#include <queue>
#include <string>
#include <string_view>
#include <thread>
#include "debug.h"
class Logger
{
public:
    ~Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;

    static void appendLog(std::string_view str);
#ifdef IS_DEBUG
    static void appendExecutionLog(std::string_view str);
#endif // IS_DEBUG

    void append(std::string_view str, std::queue<std::string>& queue);
    static void close();

private:
    static Logger& get();
    Logger();
    void flush();

    std::ofstream m_fileStream;
    std::queue<std::string> m_logQueue;
#ifdef IS_DEBUG
    std::ofstream m_executionFileStream;
    std::queue<std::string> m_executionLogQueue;
#endif // IS_DEBUG
    std::thread m_loggingThread; 
    bool m_isRunning {true};
};
