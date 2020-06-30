#include "logparser.h"
#include <filesystem>
#include <sstream>

void LogParser::addParsedLogPriority(std::string priority) 
{
    m_parsedPriorities.push_back(std::move(priority)); 
}

void LogParser::setInputFilePath(std::string path) 
{
    std::filesystem::path userPath {path};
    if (!std::filesystem::exists(userPath)) throw std::runtime_error("Cannot parse a file that does not exists : " + path);
    
    m_input = std::move(path);
}

void LogParser::setOutputFilePath(std::string path) 
{
    std::filesystem::path userPath {path};
    if (!userPath.has_filename() && !std::filesystem::exists(userPath) &&
        !std::filesystem::create_directories(userPath))
        throw std::runtime_error("Could not create directory " + path);
    
    m_output = std::move(path);
}

void LogParser::setStartDate(std::string date)
{
    struct std::tm tm{};
    std::istringstream ss(date.c_str());
    ss >> std::get_time(&tm, "%D"); 
    m_startDate = std::mktime(&tm);
}

void LogParser::setEndDate(std::string date) 
{
    struct std::tm tm{};
    std::istringstream ss(date.c_str());
    ss >> std::get_time(&tm, "%D");
    m_endDate = std::mktime(&tm);
}

void LogParser::setSortTechnique(Sort sort) 
{
    m_sort = sort;
}

void LogParser::exec()
{

}