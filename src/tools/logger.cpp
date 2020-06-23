#include "logger.h"

#include <filesystem>
#ifdef _WIN32
    #include <ShlObj.h>
#endif
#include <thread>

namespace
{
std::filesystem::path getLogPath()
{
    constexpr std::string_view folderName {"PotatoThunder/UneEtoile/"};
    std::filesystem::path programDataPath;
#ifdef _WIN32
    PWSTR path {NULL};
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramData, KF_FLAG_DEFAULT, NULL, &path);
    if (SUCCEEDED(hr)) programDataPath = path;
#endif
    programDataPath.append(folderName);
    if (!std::filesystem::exists(programDataPath))
        std::filesystem::create_directories(programDataPath);
    return programDataPath;
}
} // namespace

void Logger::append(std::string_view str)
{
    Logger& logger {get()};
    logger.m_logQueue.push(std::string(str));
}

void Logger::close()
{
    get().m_isRunning = false;
}

Logger& Logger::get()
{
    static Logger log;
    return log;
}

Logger::Logger()
{
    m_fileStream.open(getLogPath(), std::ios_base::out | std::ios_base::app);
    if (m_fileStream.is_open())
    {
        std::thread thread {&Logger::flush, this};
        thread.detach();
    }
}

Logger::~Logger()
{
    close();
    std::this_thread::sleep_for(std::chrono::milliseconds {600});
}

void Logger::flush()
{
    while (m_isRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds {500});
        while (!m_logQueue.empty())
        {
            m_fileStream << m_logQueue.front();
            m_logQueue.pop();
        }
    }
    m_fileStream.close();
}
