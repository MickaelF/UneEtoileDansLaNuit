#include "logger.h"

#include <filesystem>
#ifdef _WIN32
    #include <ShlObj.h>
#endif
#include <sstream>

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

constexpr std::string_view logFileName {"log.txt"};
constexpr std::string_view executionFileName {"execution.txt"};
} // namespace

Logger::Logger()
{
    auto basePath {getLogPath()};
    
    auto logPath = basePath; 
    logPath.append(logFileName);
    m_fileStream.open(logPath, std::ios_base::out | std::ios_base::app);
    bool isOpened = m_fileStream.is_open(); 
#ifdef IS_DEBUG
    auto executionLogPath = basePath;
    executionLogPath.append(executionFileName);
    m_executionFileStream.open(executionLogPath, std::ios_base::out | std::ios_base::app);
    isOpened = isOpened && m_executionFileStream.is_open();
#endif // IS_DEBUG
    if (isOpened)
    {
        m_loggingThread = std::thread{&Logger::flush, this};
    }
}

Logger::~Logger()
{
    close();
}

void Logger::appendLog(std::string_view str)
{
    get().append(str, get().m_logQueue);
}

#ifdef IS_DEBUG
void Logger::appendExecutionLog(std::string_view str)
{
    get().append(str, get().m_executionLogQueue);
}
#endif

void Logger::append(std::string_view str, std::queue<std::string>& queue)
{
    std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&end_time), "[%D-%T]");
    queue.push(ss.str() + std::string(str));
}

void Logger::close()
{
    Logger& logger {get()};
    logger.m_isRunning = false;
    logger.m_loggingThread.join();
}

Logger& Logger::get()
{
    static Logger log;
    return log;
}

void Logger::flush()
{
    while (m_isRunning)
    {
        if (!m_logQueue.empty())
        {
            while (!m_logQueue.empty())
            {
                m_fileStream << m_logQueue.front();
                m_logQueue.pop();
            }
            m_fileStream << std::flush;
        }

#ifdef IS_DEBUG
        if (!m_executionLogQueue.empty())
        {
            while (!m_executionLogQueue.empty())
            {
                m_executionFileStream << m_executionLogQueue.front();
                m_executionLogQueue.pop();
            }
            m_executionFileStream << std::flush;
        }
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds {500});
    }
    m_fileStream.close();
}
