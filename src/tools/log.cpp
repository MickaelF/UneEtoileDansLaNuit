#include "log.h"
#include "debug.h"
#include "logger.h"

#ifdef IS_DEBUG
    #include <iostream>
#endif

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

Log::Log(Priority priority, std::string_view fileName, int lineNumber) : m_priority(priority)
{
    m_stream << "[" << enumToStr(priority) << "-"
             << fileName.substr(fileName.find_last_of('\\') + 1) << ":" << lineNumber << "] - ";
}

Log::~Log()
{
#ifdef IS_DEBUG
    static std::mutex m_mutex;
    std::lock_guard<std::mutex> lock {m_mutex};
    std::cout << m_stream.str() << std::endl;
#endif
    Logger::appendLog(m_stream.str()+"\n");
}
