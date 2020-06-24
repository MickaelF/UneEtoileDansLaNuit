#include "log.h"

#include <iostream>

#include "logger.h"

namespace
{
const char* enumToStr(Log::Priority p)
{
    switch (p)
    {
        case Log::Priority::Debug: return "Debug";
        case Log::Priority::Info: return "Info";
        case Log::Priority::Warning: return "Warning";
        case Log::Priority::Error: return "Error";
        case Log::Priority::Fatal: return "Fatal";
        case Log::Priority::Remember: return "Remember";
        default: return "Unknown";
    }
}
} // namespace
std::mutex Log::m_mutex;

Log::Log(Priority priority, std::string_view fileName, int lineNumber) : m_priority(priority)
{
    m_stream << "[" << enumToStr(priority) << "-"
             << fileName.substr(fileName.find_last_of('\\') + 1) << ":" << lineNumber << "] - ";
}

Log::~Log()
{
    std::lock_guard<std::mutex> lock {m_mutex};
    std::cout << m_stream.str() << std::endl;
    Logger::appendLog(m_stream.str()+"\n");
}
